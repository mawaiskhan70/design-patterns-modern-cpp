# Interface Segregation Principle (ISP) — Product Filter

## Definition
> Clients should NOT be forced to depend on interfaces they don't use.
> Many small, specific interfaces are better than one large, general interface.

---

## The Problem — Without ISP

```
❌ Old approach: Two coupled concepts in related interfaces

Specification<T>     ← Checking criteria
Filter<T>            ← Filtering items

Problem:
  What if you ONLY need to check one product?
  → Still forced to know about Filter!
  
  What if you ONLY need to filter?
  → Still forced to know about Specification details!
  
  What if you want to combine specs?
  → Mixed into Specification — not a separate concern!
```

---

## The Solution — With ISP

```
✅ Three SEPARATE, focused interfaces:

ISpecification<T>    → ONLY checks if item matches criteria
IFilter<T>           → ONLY filters items using a specification
ICombiner            → ONLY combines specifications via operator&&

Each interface = ONE focused job!
Each client depends ONLY on what it needs!
```

---

## Interface Design

### ISpecification — Checking ONLY
```cpp
template <typename T>
class ISpecification {
    virtual bool is_satisfied(T* item) const = 0;
};

// Usage: Check one item against criteria
// Does NOT filter collections
// Does NOT combine with other specs
```

### IFilter — Filtering ONLY
```cpp
template <typename T>
class IFilter {
    virtual vector<T*> filter(vector<T*> items,
                              ISpecification<T>& spec) = 0;
};

// Usage: Filter a collection using any specification
// Does NOT define what criteria to check
// Does NOT combine specifications
```

### ICombiner — Combining ONLY
```cpp
template <typename T>
AndSpecification<T> operator&&(const ISpecification<T>& first,
                                const ISpecification<T>& second);

// Usage: Combine two specifications into one
// Does NOT check items
// Does NOT filter collections
```

---

## Project Structure

```
ProductFilter-ISP/
├── main.cpp
├── model/
│   ├── product.h                   ← Data model
│   └── product.cpp
├── interfaces/
│   ├── ISpecification.h            ← Checking (CLOSED)
│   ├── IFilter.h                   ← Filtering (CLOSED)
│   └── ICombiner.h                 ← Combining (CLOSED)
└── filters/
    ├── ColorSpecification.h/.cpp   ← Implements ISpecification
    ├── SizeSpecification.h/.cpp    ← Implements ISpecification
    ├── AndSpecification.h          ← Combines ISpecifications
    └── BetterFilter.h/.cpp         ← Implements IFilter
```

---

## ISP in Action — Functions Take ONLY What They Need

### Check One Product (Needs ONLY ISpecification)
```cpp
// ✅ Takes ONLY ISpecification — no filter dependency!
bool checkProduct(ISpecification<Product>& spec, Product* product) {
    return spec.is_satisfied(product);
}

// Usage:
ColorSpecification green(Color::green);
checkProduct(green, &apple);    // Just checks — no filtering!
```

### Filter Products (Needs IFilter + ISpecification)
```cpp
// ✅ Takes IFilter and ISpecification — focused!
vector<Product*> filterProducts(IFilter<Product>& filter,
                                 vector<Product*> items,
                                 ISpecification<Product>& spec) {
    return filter.filter(items, spec);
}
```

### Combine Specifications (Needs ONLY ICombiner)
```cpp
// ✅ Uses operator&& from ICombiner — no filter dependency!
auto green_and_large = green && large;
// Creates AndSpecification that checks BOTH
```

---

## ISP Benefit — Use Interfaces Independently

```
┌─────────────────────────────────────────────────────┐
│                                                     │
│  Need to CHECK one item?                            │
│  → Use ISpecification alone ✅                     │
│  → No dependency on IFilter or ICombiner            │
│                                                     │
│  Need to FILTER collection?                         │
│  → Use IFilter + ISpecification ✅                 │
│  → No dependency on ICombiner                       │
│                                                     │
│  Need to COMBINE criteria?                          │
│  → Use ICombiner + ISpecification ✅               │
│  → No dependency on IFilter                         │
│                                                     │
│  Need ALL?                                          │
│  → Use all three ✅                                │
│  → But each part is independent!                    │
│                                                     │
└─────────────────────────────────────────────────────┘
```

---

## Adding New Feature — Easy!

### Want to add "filter by price"?

```
Step 1: Create PriceSpecification
   → Implements ISpecification only
   → No changes to IFilter or ICombiner!

Step 2: Use it
   PriceSpecification cheap(Price::low);
   
   // Check single item — uses ISpecification
   checkProduct(cheap, &apple);
   
   // Filter items — uses IFilter + ISpecification
   filterProducts(bf, all, cheap);
   
   // Combine — uses ICombiner + ISpecification
   auto cheap_and_green = cheap && green;

Nothing existing changes! ✅
```

### Want to add "OR combiner"?

```
Step 1: Create OrSpecification
   → Implements ISpecification
   → New operator|| in ICombiner

Step 2: Use it
   auto green_or_large = green || large;

IFilter unchanged! ✅
Existing specifications unchanged! ✅
```

---

## Polymorphism with ISP

### Same Function, Different Specifications
```cpp
// checkProduct accepts ANY ISpecification
checkProduct(green, &apple);       // Color check
checkProduct(large, &tree);        // Size check
checkProduct(green_and_large, &tree); // Combined check

// All work because they ALL implement ISpecification!
```

### Same Filter, Different Specifications
```cpp
BetterFilter bf;

bf.filter(all, green);             // Filter by color
bf.filter(all, large);             // Filter by size
bf.filter(all, green_and_large);   // Filter by both

// BetterFilter doesn't know WHAT it's filtering by!
// It just calls spec.is_satisfied() — ISP + Polymorphism!
```

---

## Comparison: Before vs After ISP

```
┌──────────────────────┬──────────────────┬───────────────────┐
│ Feature              │ Without ISP      │ With ISP          │
├──────────────────────┼──────────────────┼───────────────────┤
│ Check one item       │ Need Filter too  │ ISpecification ✅ │
│ Filter collection    │ Coupled to Spec  │ IFilter + ISpec ✅│
│ Combine specs        │ Mixed in Spec    │ ICombiner ✅      │
│ Add new criteria     │ Touch Filter too │ Only new Spec ✅  │
│ Independent usage    │ ❌ No            │ ✅ Yes            │
│ Focused interfaces   │ ❌ No            │ ✅ Yes            │
│ Forced dependencies  │ ❌ Yes           │ ✅ None           │
└──────────────────────┴──────────────────┴───────────────────┘
```

---

## How All SOLID Principles Work Together Here

```
┌──────────────────────────────────────────────────────────┐
│                                                          │
│  SRP: Each class ONE job                                 │
│    ColorSpecification → only checks color                │
│    SizeSpecification  → only checks size                 │
│    BetterFilter       → only filters                     │
│                                                          │
│  OCP: Open for extension, closed for modification        │
│    ISpecification     → CLOSED (never changes)           │
│    New specs          → OPEN (just add new class)        │
│                                                          │
│  ISP: Small, focused interfaces                          │
│    ISpecification     → ONLY checking                    │
│    IFilter            → ONLY filtering                   │
│    ICombiner          → ONLY combining                   │
│    Each client uses ONLY what it needs!                  │
│                                                          │
│  Together:                                               │
│    SRP → WHAT to separate                                │
│    OCP → HOW to make extensible                          │
│    ISP → HOW to design clean interfaces                  │
│                                                          │
└──────────────────────────────────────────────────────────┘
```

---

## Summary

```
┌──────────────────────────────────────────────────────────┐
│                                                          │
│  ISP = Don't force unnecessary dependencies              │
│                                                          │
│  1. Split responsibilities into small interfaces         │
│     ISpecification (check) + IFilter (filter)            │
│     + ICombiner (combine)                                │
│                                                          │
│  2. Each function takes SMALLEST interface needed        │
│     checkProduct(ISpecification&) — no filter needed     │
│     filterProducts(IFilter&, ISpecification&)            │
│                                                          │
│  3. Classes implement ONLY what they do                  │
│     ColorSpec → ISpecification only                      │
│     BetterFilter → IFilter only                          │
│                                                          │
│  4. Combine when needed                                  │
│     AndSpecification → ISpecification (is a combined)    │
│     operator&& → creates AndSpecification                │
│                                                          │
└──────────────────────────────────────────────────────────┘
```
