
# Prototype via Serialization (Header-Only Manual Implementation)

## What is Serialization?

Serialization is the process of converting an object's data into a **sequence of bytes** (a byte stream).  
Deserialization is the reverse process — converting that byte stream back into a live object in memory.

In this project, we implemented **manual binary serialization** using `std::stringstream`, without depending on any external library like Boost.

## Why Use Serialization for Prototype Pattern?

The main goal of the Prototype pattern is to create a **deep copy** of an object.

In Project 1 and Project 2, we achieved deep copy using the **copy constructor**.  
However, as classes become more complex, writing and maintaining correct copy constructors becomes difficult and error-prone.

**Serialization solves this elegantly** by:
- Converting the entire object into bytes
- Creating a completely new object from those bytes
- Guaranteeing a true deep copy without relying on copy constructors

This is a very powerful and commonly used technique in real-world applications.

---

## How This Approach Works

We added two methods to both `Address` and `Contact` classes:

- `void serialize(std::ostream& os) const` → Writes object data as bytes into a stream
- `static T deserialize(std::istream& is)` → Reads bytes from a stream and creates a new object

### The Clone Function (Lambda)

```cpp
auto cloneViaSerialization = [](const Contact& original) -> std::unique_ptr<Contact>
{
    std::stringstream buffer(std::ios::in | std::ios::out | std::ios::binary);
    
    original.serialize(buffer);     // Step 1: Convert object → bytes
    buffer.seekg(0);                // Reset read position to beginning
    return std::make_unique<Contact>(Contact::deserialize(buffer)); // Step 2: bytes → new object
};
```

**Note**: We used `[]` (empty capture) because this lambda does not need to access any variables from the surrounding scope.

---

## Dry Run of the Serialization Process

1. `original.serialize(buffer)`  
   - Writes `name`, `hasAddress` flag, and `Address` data as raw bytes into the `std::stringstream`.

2. `buffer.seekg(0)`  
   - Moves the reading pointer back to the start of the buffer.

3. `Contact::deserialize(buffer)`  
   - Reads the bytes in the same order.
   - Reconstructs a **brand new** `Contact` object with its **own new** `Address` object.

Result: A perfect **deep copy** is created.

The `std::stringstream` acts as a **temporary in-memory pipe** between serialization and deserialization.

---

## Comparison with Previous Two Projects

| Feature                        | Project 1 (Basic Prototype) | Project 2 (Prototype Factory) | Project 3 (Serialization)              |
|--------------------------------|-----------------------------|-------------------------------|----------------------------------------|
| Deep Copy Technique            | Copy Constructor            | Copy Constructor              | Serialize + Deserialize                |
| Need to maintain copy ctor     | Yes                         | Yes                           | No                                     |
| Difficulty with complex objects| High                        | High                          | Low                                    |
| Dependencies                   | None                        | None                          | None (manual)                          |
| Reusability of prototype       | Good                        | Excellent                     | Excellent                              |
| Code maintainability           | Medium                      | Good                          | Very Good                              |
| Best For                       | Learning deep copy          | Real-world simple cases       | Complex objects / future-proofing      |

**Key Difference**:  
This version does **not** rely on the copy constructor at all. It uses a completely different mechanism — converting the object to bytes and back.

---

## Benefits of This Serialization Approach

| Benefit                              | Explanation                                                                 |
|--------------------------------------|-----------------------------------------------------------------------------|
| **No External Dependencies**         | Works without Boost or any third-party library                             |
| **True Deep Copy**                   | Creates completely independent objects                                     |
| **Scalable**                         | Easy to add new fields — just update serialize/deserialize methods         |
| **Future-Proof**                     | Can later be extended to save to files or send over network                |
| **Cleaner for Complex Objects**      | Much easier than writing deep copy constructors for complicated classes    |
| **Educational Value**                | Clearly demonstrates the concept of serialization                          |

---

## Additional Features This Approach Provides

- You can easily change the destination from `std::stringstream` to `std::ofstream` to save objects to files.
- You can send serialized objects over the network.
- You can add versioning support in the future.
- Works safely with `std::unique_ptr`.

---


## When to Use This Approach?

**Use Prototype via Serialization when:**
- You need deep copy but copy constructor is hard to maintain
- Objects may become complex in the future
- You want a clean solution without external libraries
- You want to learn the core concept of serialization

**Use Project 1 or 2 when:**
- Objects are simple and copy constructor is easy to write

---

## Summary & Revision Points

- **Serialization** = Object → Byte Stream → New Object
- This is the **third way** to implement the Prototype pattern
- It uses manual binary serialization with `std::stringstream`
- `serialize()` writes data, `deserialize()` reads data and creates new objects
- The lambda `[](const Contact& original)` defines a small inline cloning function
- This approach is **dependency-free**, scalable, and very educational
