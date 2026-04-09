
# 📝 Prototype Pattern — Complete Revision Notes

## What is the Prototype Pattern?

**Prototype Pattern** = Create new objects by **cloning** an existing object (the "Prototype") instead of constructing them from scratch every time using `new` or long constructors.

**Core Idea:**
> "Don't create from scratch — just give me a copy of this ready object and let me modify only what I need."

---

## Why Do We Need the Prototype Pattern?

### Common Problems Without It:
1. **Code Duplication** — Writing the same initialization code again and again for similar objects.
2. **Shallow Copy Bugs** — Very common mistake when doing `Contact jane = john;`
3. **Complex Object Creation** — Constructors with many parameters become confusing and error-prone.
4. **Maintenance Nightmare** — Adding a new field requires updating creation code in many places.

**Prototype solves all these** by providing a clean way to clone objects.

---

## Deep Copy vs Shallow Copy (Very Important Concept)

| Feature                  | Shallow Copy                                      | Deep Copy                                              |
|--------------------------|---------------------------------------------------|--------------------------------------------------------|
| What is copied?          | Only the pointer / reference                      | The actual data (new object is created)                |
| Example                  | `Contact jane = john;` (copies pointer)           | `Contact jane{employee_proto};` (using copy ctor)      |
| Result                   | Both objects share the same `Address`             | Each object has its own independent `Address`          |
| Risk                     | High — changing one affects the other             | Safe — objects are completely independent              |
| Memory                   | Less memory (shared data)                         | More memory (duplicate data)                           |

### Visual Example:

```cpp
// Shallow Copy (Dangerous)
Contact jane = john;
jane.setSuite(999);        // This also changes john's suite!

// Deep Copy (Safe - What Prototype does)
Contact jane{employee_proto};   // Calls copy constructor
jane.setSuite(999);             // Only jane is affected
```

**Rule of Thumb:**  
Whenever your class contains pointers or `unique_ptr`, you **must** implement deep copy (either via copy constructor or serialization).

---

## Three Implementations of Prototype Pattern

### 1. Basic Prototype (Using Copy Constructor)

```cpp
Contact employee_proto{"Unknown", std::make_unique<Address>("123 East Dr", "London", 0)};

Contact john{employee_proto};     // Deep copy via copy constructor
john.setName("John Doe");
john.setSuite(123);
```

**Key Points:**
- Uses custom copy constructor
- `std::unique_ptr<Address>` ensures safe memory management
- Simple and good for learning

---

### 2. Prototype Factory (Most Practical)

```cpp
auto john = EmployeeFactory::NewMainOfficeEmployee("John Doe", 123);
auto jane = EmployeeFactory::NewAuxOfficeEmployee("Jane Doe", 125);
```

**Key Points:**
- Static prototypes stored inside factory (`main_office`, `aux_office`)
- Factory clones the prototype and applies small customizations
- Returns `std::unique_ptr<Contact>`
- Prototypes are created only once and reused many times

**Best real-world usage.**

---

### 3. Prototype via Serialization (Manual Header-Only)

```cpp
auto cloneViaSerialization = [](const Contact& original) -> std::unique_ptr<Contact>
{
    std::stringstream buffer(std::ios::in | std::ios::out | std::ios::binary);
    original.serialize(buffer);      // Object → Bytes
    buffer.seekg(0);
    return std::make_unique<Contact>(Contact::deserialize(buffer)); // Bytes → New Object
};
```

**Key Points:**
- No need to write copy constructor
- Uses `serialize()` and `deserialize()` methods
- Works great when objects are complex
- Fully self-contained (no Boost)

---

## Comparison Table (Must Remember)

| Implementation             | Deep Copy Method            | Copy Constructor Needed? | Complexity | When to Use                              |
|---------------------------|-----------------------------|---------------------------|------------|------------------------------------------|
| Basic Prototype           | Copy Constructor            | Yes                       | Low        | Learning, simple objects                 |
| Prototype Factory         | Copy Constructor            | Yes                       | Medium     | Most real projects (recommended)         |
| Serialization             | Serialize + Deserialize     | No                        | Medium     | Complex objects, future scalability      |

---

## Key Modern C++ Concepts Used

- `std::unique_ptr<T>` → Automatic memory management + exclusive ownership
- `std::make_unique<>()` → Safe way to create objects
- `std::move()` → Transfer ownership of `unique_ptr`
- Lambda: `[](const Contact& original) -> std::unique_ptr<Contact>`
- `std::stringstream` → In-memory byte buffer for serialization
- Deep Copy vs Shallow Copy

---

## Benefits of Prototype Pattern

- **Less duplication** — No need to repeat object creation code
- **Safety** — Avoids shallow copy bugs
- **Readability** — Clear methods like `NewMainOfficeEmployee()`
- **Maintainability** — Change prototype in one place
- **Flexibility** — Easy to create variations
- **Scalability** — Serialization version handles complex objects easily

---

## Flow Diagram (Quick Recall)

```
Create Prototype Object
        ↓
   Clone (Deep Copy)
        ↓
Customize cloned object (setName, setSuite, etc.)
        ↓
     Use the new object
```

**Factory Version Flow:**
```
Static Prototypes (main_office, aux_office)
        ↓
   EmployeeFactory clones + customizes
        ↓
   Returns unique_ptr<Contact>
```

**Serialization Version Flow:**
```
Original Object → serialize() → Byte Stream (stringstream)
                        ↓
               deserialize() → Brand New Object
```

---

## Quick Decision Guide

**Ask these questions:**
- Are objects simple? → Use **Basic Prototype** or **Prototype Factory**
- Need many similar objects? → Use **Prototype Factory**
- Objects are getting complex? → Use **Serialization**
- Want zero external dependencies? → Use **Manual Serialization**

---

## Common Pitfalls

- Using assignment (`=`) instead of copy constructor → shallow copy
- Forgetting to handle `unique_ptr` properly in copy constructor
- After `std::move()`, source pointer becomes null
- In serialization: Forgetting `seekg(0)` before reading

---

## One-Line Takeaways (Ultra Quick Revision)

- **Prototype** = Clone, don’t create from scratch
- **Basic** = Copy Constructor + Deep Copy
- **Factory** = Centralized prototypes + cloning
- **Serialization** = Object → Bytes → New Object (no copy ctor needed)
- Always prefer `unique_ptr` over raw pointers
- Shallow Copy = Shared data → Bugs | Deep Copy = Independent data → Safe

---
