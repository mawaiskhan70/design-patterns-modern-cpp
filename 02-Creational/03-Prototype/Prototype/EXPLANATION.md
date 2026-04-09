
# Prototype Pattern - Basic Deep Copy (Modern OOP with Classes + unique_ptr)

## What is the Prototype Pattern?
The **Prototype Pattern** allows us to create new objects by **cloning** an existing object (called the "prototype") instead of constructing them from scratch every time.

It is very useful when we need many similar objects with only small differences (like employees working in the same office).

---

## Problem Without Prototype Pattern

```cpp
// Repetitive and error-prone way
auto addr1 = std::make_unique<Address>("123 East Dr", "London", 123);
auto addr2 = std::make_unique<Address>("123 East Dr", "London", 125);

Contact john{"John Doe", std::move(addr1)};
Contact jane{"Jane Doe", std::move(addr2)};
```

**Even worse problem — Shallow Copy Bug:**
```cpp
Contact jane = john;        // This does SHALLOW copy!
jane.setSuite(125);         // This also changes John's address! → BUG
```

This is a very common mistake for beginners.

---

## Modern Solution — Prototype Pattern with OOP

We create **one prototype object** and then **clone** it using the copy constructor.  
We use **classes** (not structs) and **`std::unique_ptr`** for safe memory management.

---

## Important Line Explained: Creating the Prototype

```cpp
auto proto_addr = std::make_unique<Address>("123 East Dr", "London", 0);
```

### What is happening here?

1. **`std::make_unique<Address>(...)`**  
   - Creates a new `Address` object on the heap (dynamic memory).  
   - Automatically wraps it inside a `std::unique_ptr<Address>`.  
   - Calls the `Address` constructor with the given values.

2. **`auto proto_addr = ...`**  
   - `auto` tells the compiler: *"Automatically detect the type for me"*.  
   - The right side returns `std::unique_ptr<Address>`, so `auto` becomes **`std::unique_ptr<Address>`**.  
   - This makes the code short and clean.

**Simple meaning:**  
"Create a smart pointer that owns a new `Address` object and name it `proto_addr`."

---

## Why do we use `std::move(proto_addr)`?

```cpp
Contact employee_proto{"Unknown Employee", std::move(proto_addr)};
```

- `std::unique_ptr` follows **exclusive ownership** rule — **only one object can own the Address at a time**.
- `unique_ptr` **cannot be copied**. It can only be **moved** (ownership transferred).
- `std::move()` tells the compiler: "I no longer need this pointer — transfer ownership to the Contact".
- After move, `proto_addr` becomes **empty (null)**.

---

## What happens after `std::move`? (proto_addr becomes null)

After `std::move(proto_addr)`:
- `proto_addr` is now in a **"moved-from" state** → it is **null/empty**.
- You **cannot use it anymore** (`proto_addr->getStreet()` would crash or cause undefined behavior).
- This is intentional behavior of `unique_ptr` to prevent bugs.

### Corner Case: What if I need another prototype later?

**Solution:** Just create a **new** `make_unique<Address>()`.

```cpp
auto new_proto_addr = std::make_unique<Address>("456 West Rd", "Berlin", 0);
Contact another_proto{"Another Employee", std::move(new_proto_addr)};
```

You cannot reuse the moved-from `proto_addr`. Always create fresh ones when needed.

---

## Benefits of This Modern Design (Classes + unique_ptr)

| Benefit                        | Explanation                                                                 |
|--------------------------------|-----------------------------------------------------------------------------|
| **Memory Safety**              | No manual `delete`. `unique_ptr` cleans up automatically                   |
| **No Memory Leaks**            | Even if exception happens, memory is freed safely                          |
| **Exclusive Ownership**        | Only one `Contact` owns the `Address` at a time → prevents bugs            |
| **Deep Copy Made Easy**        | Copy constructor simply does `make_unique<Address>(*other.address)`        |
| **Better OOP**                 | Private members + getters/setters → proper encapsulation                   |
| **Less Boilerplate**           | No need to write destructor manually (Rule of Three/ Five simplified)      |
| **Safer Code**                 | Compiler helps catch many common mistakes                                  |

This design is much cleaner and safer than using raw pointers (`Address*`).

---

## How the Prototype Pattern Works Here

1. Create prototype `Address` using `make_unique`
2. Pass ownership to `Contact` using `std::move`
3. Clone `Contact` using copy constructor → deep copy of `Address` happens automatically
4. Customize cloned objects (`setName()`, `setSuite()`)

Each cloned `Contact` gets its **own independent** `Address`.

---


## When to Use the Prototype Pattern?
**Use it when:**
- You need many similar objects with small variations
- Object creation is repetitive
- You want to avoid shallow copy bugs

**Don't use it when:**
- The object is very simple (only 1-2 fields)

---

## Summary & Revision Points

- `auto` + `make_unique` = modern, clean way to create owned objects
- `std::move` = transfer ownership of `unique_ptr` (source becomes null)
- After move, always create a **new** `make_unique` if you need another prototype
- `unique_ptr` enforces **"Only one object owns the Address at a time"**
- Copy constructor is the heart of the Prototype pattern — it performs deep copy

