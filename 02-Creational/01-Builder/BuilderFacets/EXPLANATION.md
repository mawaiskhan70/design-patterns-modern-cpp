# Builder Facets Pattern

## Definition
> When an object has multiple groups of related properties,
> use separate builders (facets) for each group,
> all working on the same object.

---

## Why Builder Facets?

### Problem: Too Many Fields, No Grouping
```
Person has 6+ fields:
  Address: street, postcode, city
  Job: company, position, income

With setters:
  p.setStreet("...");     ← Which group?
  p.setCompany("...");    ← Mixed up!
  p.setPostCode("...");   ← Hard to read!
  p.setPosition("...");   ← No structure!

With builder facets:
  Person::create()
      .lives()                      ← Address group
          .at("123 London Road")
          .with_postcode("SW1 1GB")
          .in("London")
      .works()                      ← Job group
          .at("PragmaSoft")
          .as_a("Consultant")
          .earning(10000000);
```

---

## How It Works

### The Chain
```
Person::create()     → Returns PersonBuilder
    .lives()         → Returns PersonAddressBuilder
        .at(...)     → Returns PersonAddressBuilder (chaining)
        .in(...)     → Returns PersonAddressBuilder (chaining)
    .works()         → Returns PersonJobBuilder
        .at(...)     → Returns PersonJobBuilder (chaining)
        .earning(..) → Returns PersonJobBuilder (chaining)
```

### Key: ALL Builders Share SAME Person Object!
```
PersonBuilder owns Person p
    │
    ├── PersonAddressBuilder gets Person& reference
    │   └── Modifies p.street_address, p.city...
    │
    └── PersonJobBuilder gets Person& reference
        └── Modifies p.company_name, p.position...

All modify the SAME Person object!
```

---

## Class Hierarchy
```
PersonBuilderBase (has Person& reference)
├── lives() → returns PersonAddressBuilder
├── works() → returns PersonJobBuilder
└── operator Person() → converts to final Person

PersonBuilder : PersonBuilderBase (OWNS the Person)
PersonAddressBuilder : PersonBuilderBase (sets address fields)
PersonJobBuilder : PersonBuilderBase (sets job fields)
```

---

## Why Private Constructor?
```
Person() is PRIVATE!

Person p;              ← ❌ Can't create directly!
Person::create()       ← ✅ Only way! Returns builder!

This FORCES use of builder pattern.
Can't create invalid/half-built Person objects!
```

## Why Friend Classes?
```
Person fields are PRIVATE!
Builders need access to set them.
friend class PersonAddressBuilder; ← grants access
friend class PersonJobBuilder;     ← grants access
```

## Why Move Semantics?
```
operator Person() { return std::move(person); }

Builder creates Person internally.
When done, MOVES it out (no copy!).
Original builder's Person becomes empty.
Efficient! No unnecessary copies!
```

---

## Setters vs Builder Facets
```
┌───────────────────┬──────────────────┬──────────────────┐
│ Feature           │ Setters          │ Builder Facets   │
├───────────────────┼──────────────────┼──────────────────┤
│ Grouping          │ ❌ Flat          │ ✅ Grouped       │
│ Readability       │ OK               │ Great            │
│ Invalid objects?  │ ❌ Possible      │ ✅ Prevented     │
│ Forced usage      │ ❌ Optional      │ ✅ Required      │
│ Method chaining   │ Possible         │ Built-in         │
│ Field discovery   │ ❌ All mixed     │ ✅ .lives().works()│
│ Complexity        │ Simple           │ More code        │
│ Use when          │ Simple classes   │ Complex classes  │
└───────────────────┴──────────────────┴──────────────────┘
```

---

## Summary
```
Builder Facets = Multiple builders for one object
Each builder = One group of related fields
All builders share same object via reference
Private constructor forces builder usage
.lives() and .works() switch between builders
Clean, grouped, readable construction!
```
