
# Prototype Factory Pattern (Modern OOP with Classes + unique_ptr)

## What is Prototype Factory Pattern?

Prototype Factory = **Prototype Pattern + Factory Pattern combined**.

Instead of creating a prototype object every time in `main()`, we keep **static prototype objects** inside the factory.  
The factory is responsible for **cloning** these prototypes and customizing them (name, suite, etc.).

This is the most practical and commonly used version of Prototype in real projects.

---

## Problem It Solves (Why We Need It)

**Without Factory (from previous project):**
```cpp
// We had to create prototype manually every time
auto proto_addr = std::make_unique<Address>("123 East Dr", "London", 0);
Contact employee_proto{"Unknown", std::move(proto_addr)};

Contact john{employee_proto};
john.setName("John Doe");
john.setSuite(123);
```

→ Too much repeated code  
→ Easy to make mistakes  
→ Prototypes are scattered in client code

**With Prototype Factory:**
All prototype templates are **centralized** inside `EmployeeFactory`.  
Client code only calls clean factory methods:

```cpp
auto john = EmployeeFactory::NewMainOfficeEmployee("John Doe", 123);
auto jane = EmployeeFactory::NewAuxOfficeEmployee("Jane Doe", 125);
```

---

## How It Is Different from Basic Prototype (Project 1)

| Feature                        | Basic Prototype (Project 1)               | Prototype Factory (Project 2)                     |
|--------------------------------|-------------------------------------------|----------------------------------------------------|
| Where prototype is created     | In `main()` or client code                | Inside Factory (static members)                    |
| Code duplication               | High (repeat prototype creation)          | Low (centralized in factory)                       |
| Reusability                    | Manual cloning every time                 | Very high — just call factory method               |
| Maintenance                    | Difficult (change address → edit many places) | Easy (change once in factory)                   |
| Real-world usage               | Good for learning                         | Much better for actual applications                |
| Ownership of prototypes        | Temporary                                 | Static — lives for entire program                  |

**Main Difference**:  
Basic Prototype = "I create prototype myself and clone it"  
Prototype Factory = "Factory manages prototypes and gives me clones whenever I ask"

---

## Key Code Explained: Deep Copy in Factory

```cpp
std::unique_ptr<Contact> EmployeeFactory::NewEmployee(const std::string& name, int suite, const Contact& prototype)
{
    auto result = std::make_unique<Contact>(prototype); // Prototype clone (deep copy)
    result->setName(name);
    result->setSuite(suite);
    return result;
}
```

### What is happening here?

- `std::make_unique<Contact>(prototype)` → Calls **Contact's copy constructor**
- Copy constructor does **deep copy** of the `Address` (creates a completely new `Address` object)
- `result` gets its **own independent** `Address`
- We then customize only `name` and `suite`

### Important Question: Does `main_office` or `aux_office` become null?

**No!** They do **not** become null.

**Why?**

- In the first project, we used `std::move(proto_addr)` → we **moved** ownership away from `proto_addr`.
- In this factory, we pass `const Contact& prototype` (by **reference**).
- We call `Contact(prototype)` → this invokes the **copy constructor**, **not** move.
- The original `main_office` and `aux_office` remain untouched and fully reusable.

Because they are **`static`** members, they are created only **once** when the program starts and live until the program ends.  
We can call `NewMainOfficeEmployee()` hundreds of times — the prototypes are never consumed.

---

## Benefits of Prototype Factory Pattern

| Benefit                              | Explanation                                                                 |
|--------------------------------------|-----------------------------------------------------------------------------|
| **Centralized Creation**             | All office templates are in one place (easy to maintain)                   |
| **Less Code Duplication**            | No need to create prototypes again and again                               |
| **Clear Intent**                     | `NewMainOfficeEmployee()` clearly tells what we are creating               |
| **Reusability**                      | Prototypes are static → can be used forever                                |
| **Deep Copy Safety**                 | Every employee gets its own independent `Address`                          |
| **Easy to Extend**                   | Want to add "Berlin Office"? Just add new static prototype                 |
| **Memory Safety**                    | `unique_ptr` handles all memory automatically                              |

This version follows the **Single Responsibility Principle** — factory is responsible for creation, client code only consumes.

---

## What are `static` members in EmployeeFactory?

```cpp
static Contact main_office;
static Contact aux_office;
```

- `static` = belongs to the **class**, not to any object
- Created only **once** when program starts
- Shared by all calls to the factory
- Live for the entire lifetime of the program
- Perfect for holding reusable prototype templates

---

## When to Use Prototype Factory?

**Use when:**
- You have a few base templates (offices, documents, configurations, etc.)
- You need to create many similar objects with small changes
- You want centralized and clean creation logic

**Don't use when:**
- You need completely different types of objects (then Abstract Factory is better)

---

## Summary & Revision Points

- Prototype Factory = Prototype + Factory working together
- Prototypes are stored as `static Contact` inside factory
- We use **copy constructor** (`make_unique<Contact>(prototype)`) → deep copy happens
- Original prototypes (`main_office`, `aux_office`) are **never moved**, only copied → always reusable
- `unique_ptr` ensures safe memory management and exclusive ownership
- Much cleaner and more maintainable than basic Prototype
