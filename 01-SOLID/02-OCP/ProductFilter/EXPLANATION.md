# Open/Closed Principle (OCP)

## Definition
> Software entities should be **OPEN for extension** but **CLOSED for modification**.
> Add new functionality by writing NEW code, NOT by changing OLD code.

---

## The Problem — WITHOUT OCP

```cpp
// ❌ BAD: ProductFilter class
struct ProductFilter {
    Items by_color(Items items, Color color);         // Filter 1
    Items by_size(Items items, Size size);             // Filter 2
    Items by_size_and_color(Items items, Size, Color); // Filter 3
    // Items by_weight(Items items, Weight weight);    // Filter 4 — MODIFY class!
    // Items by_color_and_weight(...)                  // Filter 5 — MODIFY again!
    // NEVER ENDING MODIFICATIONS! 😩
};
```

**Problem:** Every new filter criteria requires MODIFYING the existing class.
- 2 criteria = 3 functions (A, B, A+B)
- 3 criteria = 7 functions (A, B, C, AB, AC, BC, ABC)
- N criteria = 2^N - 1 functions! 💥

---

## The Solution — WITH OCP

### Step 1: Create Specification Interface (CLOSED)
```cpp
template <typename T>
class Specification {
public:
    virtual bool is_satisfied(T* item) const = 0;
};
```
This NEVER changes. It's the contract.

### Step 2: Create Filter Interface (CLOSED)
```cpp
template <typename T>
class Filter {
public:
    virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
};
```
This NEVER changes either.

### Step 3: Add New Filters by EXTENDING (OPEN)
```cpp
// New criteria? Just create NEW class!
class ColorSpecification : public Specification<Product> {
    bool is_satisfied(Product* item) const override {
        return item->color == color;
    }
};

class SizeSpecification : public Specification<Product> {
    bool is_satisfied(Product* item) const override {
        return item->size == size;
    }
};

// Combine ANY two specifications!
class AndSpecification : public Specification<T> {
    bool is_satisfied(T* item) const override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};
```

---

## Adding New Feature — See The Difference

### Want to add "filter by weight"?

```
❌ WITHOUT OCP:
   → Open ProductFilter class
   → Add by_weight() function
   → Add by_weight_and_color() function
   → Add by_weight_and_size() function
   → Add by_weight_and_color_and_size() function
   → MODIFY existing code 😩

✅ WITH OCP:
   → Create ONE new file: WeightSpecification.h/.cpp
   → NOTHING else changes!
   → Combines automatically with && operator!
```

```cpp
// Just create NEW file — nothing else changes!
class WeightSpecification : public Specification<Product> {
    Weight weight;
    bool is_satisfied(Product* item) const override {
        return item->weight == weight;
    }
};

// Usage — automatic combination!
auto heavy_and_green = WeightSpecification{Weight::heavy}
                    && ColorSpecification{Color::green};
```

---

## Key Concepts Used

### 1. Templates
```cpp
template <typename T>
class Specification { ... };
// Works with ANY type — Product, User, Order, etc.
```

### 2. Virtual Functions (Polymorphism)
```cpp
virtual bool is_satisfied(T* item) const = 0;
// = 0 means PURE virtual — MUST be implemented by child classes
```

### 3. Operator Overloading
```cpp
template <typename T>
AndSpecification<T> operator&&(const Specification<T>& first,
                                const Specification<T>& second) {
    return { first, second };
}
// Allows: auto spec = green && large;
```

### 4. Override Keyword
```cpp
bool is_satisfied(Product* item) const override;
// override = compiler checks this actually overrides a base function
// Catches typos at compile time!
```

---

## Project Structure
```
ProductFilter/
├── main.cpp                        ← Entry point
├── model/
│   ├── Product.h/.cpp              ← Data model
├── specification/
│   ├── Specification.h             ← Interface (CLOSED)
│   ├── ColorSpecification.h/.cpp   ← Extension (OPEN)
│   ├── SizeSpecification.h/.cpp    ← Extension (OPEN)
│   └── AndSpecification.h          ← Combiner (OPEN)
└── filter/
    ├── Filter.h                    ← Interface (CLOSED)
    └── BetterFilter.h/.cpp         ← Implementation
```

## What's CLOSED (Never Changes)
- `Specification.h` — base interface
- `Filter.h` — base interface
- `BetterFilter` — works with ANY spec

## What's OPEN (Add New Without Modifying)
- New `XxxSpecification` classes
- New filter criteria
- New combinations via `&&` operator

---

## Summary
```
┌──────────────────────────────────────────────────────────┐
│                                                          │
│  OCP = Use INTERFACES + INHERITANCE                      │
│                                                          │
│  Interface (base class) → CLOSED — never modify          │
│  Implementations        → OPEN  — add new ones freely   │
│                                                          │
│  New feature = New file, NOT modified old file!          │
│                                                          │
└──────────────────────────────────────────────────────────┘
```
