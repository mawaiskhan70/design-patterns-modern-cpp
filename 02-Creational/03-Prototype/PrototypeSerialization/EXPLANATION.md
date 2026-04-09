
# Prototype via Serialization (Header-Only Manual Implementation)

## What is Serialization?
Serialization means converting an object's data into a **byte stream** (sequence of bytes) so that it can be stored or transmitted.  
Deserialization is the reverse: converting the byte stream back into a new object.

In this project, we use **manual binary serialization** (using `std::ostream` and `std::istream`) instead of Boost.

## Why Use Serialization in Prototype Pattern?

The Prototype pattern needs a **deep copy** of an object.  
When the object is simple, we can write a copy constructor.  
But when the object becomes complex (many nested objects, 3rd-party classes, etc.), writing a correct deep copy constructor becomes very difficult or impossible.

**Serialization solves this problem** by:
- Turning the entire object into bytes
- Creating a completely new object from those bytes
- Automatically performing a deep copy

This is one of the most powerful ways to implement Prototype.

---

## Problem Without Serialization (Review from Previous Projects)

**Project 1 (Basic Prototype):**  
We had to manually write a copy constructor for deep copy.

**Project 2 (Prototype Factory):**  
We relied on the copy constructor again.

Both approaches require maintaining a correct `Contact(const Contact&)` and `Address(const Address&)`.

If the class becomes very complex, this becomes error-prone and hard to maintain.

---

## Solution: Prototype via Serialization (This Project)

We added two methods to each class:
- `void serialize(std::ostream& os) const`
- `static T deserialize(std::istream& is)`

These methods convert the object to bytes and back.  
The clone function then uses an in-memory `std::stringstream` as a temporary buffer.

### How the Clone Works
```cpp
auto cloneViaSerialization = [&](const Contact& original) -> std::unique_ptr<Contact> {
    std::stringstream buffer(std::ios::in | std::ios::out | std::ios::binary);
    original.serialize(buffer);      // Step 1: Serialize to buffer
    buffer.seekg(0);                 // Reset read position
    return std::make_unique<Contact>(Contact::deserialize(buffer)); // Step 2: Deserialize
};
```

This creates a **brand new independent object** — a perfect deep copy.

---

## How It Is Different from Previous Two Approaches

| Feature                          | Project 1 (Basic Prototype) | Project 2 (Prototype Factory) | Project 3 (Serialization)          |
|----------------------------------|-----------------------------|-------------------------------|------------------------------------|
| Deep copy method                 | Copy constructor            | Copy constructor              | Serialize + Deserialize            |
| Requires manual copy constructor | Yes                         | Yes                           | No                                 |
| Works with very complex objects  | Hard                        | Hard                          | Easy                               |
| External dependencies            | None                        | None                          | None (manual)                      |
| Code maintenance                 | Medium                      | Low                           | Very low                           |
| Learning value                   | Good for beginners          | Good for real usage           | Shows advanced technique           |
| Reusability of prototype         | Good                        | Excellent                     | Excellent                          |

**Biggest advantage of this approach:**  
You don’t need to maintain a copy constructor at all.  
Even if `Contact` or `Address` becomes extremely complex later, the serialization code stays simple.

---

## Key Benefits of This Serialization Approach

| Benefit                              | Explanation                                                                 |
|--------------------------------------|-----------------------------------------------------------------------------|
| **No External Libraries**            | No Boost required — fully self-contained                                   |
| **Deep Copy Without Copy Ctor**      | Solves the hardest part of Prototype pattern                               |
| **Future-Proof**                     | Easy to add new fields — just update serialize/deserialize                 |
| **Works with unique_ptr**            | Properly handles smart pointers in serialization                           |
| **Educational**                      | Teaches binary serialization concepts clearly                              |
| **No Memory Leaks**                  | `unique_ptr` still manages memory automatically                            |

---

## What Additional Feature Does This Approach Give Us?

- **Ability to serialize to files or network** in the future (just change `stringstream` to `ofstream`/`ifstream`).
- **Versioning support** (you can add version numbers later).
- **Works even when copy constructor is deleted or impossible** (very useful with some 3rd-party libraries).

---

## When to Use Prototype via Serialization?

**Use this approach when:**
- You need deep copy but copy constructor is difficult to maintain
- You want a solution that scales to complex object graphs
- You prefer no external dependencies (like in this repo)

**Use previous approaches when:**
- Objects are simple and copy constructor is easy to write

---

## Summary & Revision Points

- **Serialization** = Convert object → bytes → new object
- This gives us **Prototype without needing a copy constructor**
- It is different from Project 1 & 2 because it uses **byte stream** instead of copy constructor
- Manual header-only implementation makes it clean, self-contained and easy to learn
- `serialize()` and `deserialize()` are the heart of this version
- Original prototype remains completely unchanged after cloning
