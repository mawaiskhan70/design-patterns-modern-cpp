# Builder Facets Pattern — Complete Revision Notes

## What is Builder Pattern?
```
Build COMPLEX objects step by step
instead of one giant constructor with 10+ parameters.

❌ Without Builder:
Person p("123 London", "SW1", "London", "PragmaSoft", "Consultant", 10000000);
// Which parameter is what?? 😩

✅ With Builder:
Person p = Person::create()
    .lives().at("123 London").with_postcode("SW1").in("London")
    .works().at("PragmaSoft").as_a("Consultant").earning(10000000);
// Crystal clear! 🎯
```

---

## What is Builder FACETS?
```
When object has MULTIPLE GROUPS of related properties,
use SEPARATE builders (facets) for each group.

Person has TWO groups:
  Address: street, postcode, city
  Job: company, position, income

Each group gets its OWN builder:
  PersonAddressBuilder → handles address fields
  PersonJobBuilder     → handles job fields

Both modify the SAME Person object!
```

---

## Why Not Just Use Setters?

### Setters Approach
```cpp
Person p;
p.setStreetAddress("123 London Road");
p.setPostCode("SW1 1GB");
p.setCity("London");
p.setCompanyName("PragmaSoft");
p.setPosition("Consultant");
p.setAnnualIncome(10000000);
```

### Problems With Setters
```
Problem 1: No GROUPING
  All 6 methods are flat
  Can't see which fields belong to Address vs Job
  
Problem 2: Can FORGET fields
  Person p;
  p.setCity("London");
  // Forgot street and postcode! No one tells you! 😩
  
Problem 3: Can create INVALID objects
  Person p;           ← Object exists with EMPTY fields!
  p.setCity("London"); ← Half-built object! Invalid!
  
Problem 4: Public constructor needed
  Person p;  ← Must be able to create empty Person
  Builder forces: Person::create() ← Only way!
```

### When to Use Setters vs Builder
```
Simple class (2-3 fields)    → Setters are fine
Complex class (10+ fields)   → Use Builder
Fields need grouping         → Use Builder Facets
Must prevent invalid objects → Use Builder
```

---

## Class Hierarchy — How They Connect

```
PersonBuilderBase (has Person& reference)
│
├── lives() → returns PersonAddressBuilder
├── works() → returns PersonJobBuilder
└── operator Person() → converts builder to final Person
        │
        ├── PersonBuilder : PersonBuilderBase
        │     └── OWNS the actual Person object (Person p)
        │
        ├── PersonAddressBuilder : PersonBuilderBase
        │     └── Sets address fields (street, postcode, city)
        │
        └── PersonJobBuilder : PersonBuilderBase
              └── Sets job fields (company, position, income)
```

---

## Memory Model — Only ONE Person Exists!

```
PersonBuilder OWNS the Person:

┌─────────────────────────────┐
│ PersonBuilder               │
│                             │
│  Person p ─────────────┐    │
│    street = ""         │    │
│    city = ""           │    │
│    company = ""        │    │
│                        │    │
│  (inherited from base):│    │
│  Person& person ───────┘    │  ← SAME p! Just another name!
│                             │
└─────────────────────────────┘

When AddressBuilder created:

┌──────────────────┐
│ Person p         │  ← Still SAME one!
│   street = ""    │
└────────▲─────────┘
         │ reference (not copy!)
┌────────┴─────────────────┐
│ PersonAddressBuilder     │
│   Person& person ────────┼──► Points to SAME Person!
└──────────────────────────┘

When JobBuilder created:

┌──────────────────┐
│ Person p         │  ← Still SAME one!
│   street = "123" │
└────────▲─────────┘
         │ reference (not copy!)
┌────────┴─────────────────┐
│ PersonJobBuilder         │
│   Person& person ────────┼──► Points to SAME Person!
└──────────────────────────┘

KEY: Only ONE Person exists!
     Everyone has REFERENCE to it!
     Everyone modifies SAME Person!
```

---

## Complete Code Flow — Step by Step

### The Call
```cpp
Person p = Person::create()
    .lives().at("123 London Road").with_postcode("SW1").in("London")
    .works().at("PragmaSoft").as_a("Consultant").earning(10000000);
```

### Step 1: Person::create()
```
static PersonBuilder create() {
    return PersonBuilder{};
}

What happens:
  PersonBuilder constructor runs
  → Person p created INSIDE PersonBuilder (REAL Person born!)
  → PersonBuilderBase gets Person& reference to same p
  → Returns PersonBuilder

Memory:
  PersonBuilder {
      Person p { street="", city="", company="" }
      Person& person → points to same p
  }
```

### Step 2: .lives()
```
PersonAddressBuilder lives() const {
    return PersonAddressBuilder{ person };
}

What happens:
  → Creates PersonAddressBuilder
  → Passes SAME Person reference
  → AddressBuilder's base stores SAME reference
  → PersonBuilder goes away, but Person still exists in chain

Memory:
  PersonAddressBuilder {
      Person& person → points to SAME Person p
  }
```

### Step 3: .at("123 London Road").with_postcode("SW1").in("London")
```
Self& at(std::string street_address) {
    person.street_address = street_address;  // Modifies SAME Person!
    return *this;                            // Returns self for chaining!
}

What happens:
  → person.street = "123 London Road"   (SAME Person modified!)
  → person.postcode = "SW1"             (SAME Person modified!)
  → person.city = "London"              (SAME Person modified!)
  → Returns *this (PersonAddressBuilder) each time

Memory after:
  Person p { street="123 London", postcode="SW1", city="London" }
```

### Step 4: .works()
```
PersonJobBuilder works() const {
    return PersonJobBuilder{ person };
}

What happens:
  → AddressBuilder INHERITS from PersonBuilderBase
  → PersonBuilderBase HAS works() method
  → So AddressBuilder CAN call works()!
  → Creates PersonJobBuilder with SAME Person reference

Memory:
  PersonJobBuilder {
      Person& person → points to SAME Person p
  }
```

### Step 5: .at("PragmaSoft").as_a("Consultant").earning(10000000)
```
What happens:
  → person.company = "PragmaSoft"    (SAME Person modified!)
  → person.position = "Consultant"   (SAME Person modified!)
  → person.income = 10000000         (SAME Person modified!)
  → Returns *this (PersonJobBuilder) each time

Memory after:
  Person p {
      street = "123 London Road"
      postcode = "SW1"
      city = "London"
      company = "PragmaSoft"
      position = "Consultant"
      income = 10000000
  }
  ← Fully built! ✅
```

### Step 6: operator Person() — THE CONVERSION
```
Left side:  Person p =
            Wants a Person!

Right side: ...earning(10000000)
            Returns PersonJobBuilder!

Compiler: "I need Person, I have PersonJobBuilder"
          "Does it have operator Person()?"
          "YES! Inherited from PersonBuilderBase!"

operator Person() const {
    return std::move(person);
}

What happens:
  1. std::move(person) marks person as "ready to move"
  2. return creates TEMPORARY Person using Move Constructor
  3. Person p receives the temporary (copy elision)
  4. Person p is now complete! ✅
  5. Builder's person is now EMPTY (moved out)
```

---

## Understanding operator Person() — Conversion Operator

### What Is It?
```
operator Person() is a TYPE CONVERSION operator
NOT +, -, <<, >> operator!

It tells compiler:
"When someone wants a Person from this builder,
 HERE'S how to convert builder into Person"
```

### How It Works
```cpp
class PersonBuilderBase {
    operator Person() const {
        return std::move(person);
    }
};

// Compiler sees:
Person p = PersonJobBuilder{...};

// Compiler thinks:
// "I need Person, I have PersonJobBuilder"
// "PersonJobBuilder inherits PersonBuilderBase"
// "PersonBuilderBase has operator Person()!"
// "Call it to convert!"
```

### Without It
```cpp
// ❌ Without operator Person():
Person p = Person::create().lives()...;
// COMPILE ERROR! "Cannot convert PersonJobBuilder to Person!"

// Would need ugly explicit method:
Person p = builder.build();   // Extra step! Less clean!
```

### Simple Analogy
```
operator Person() = UNWRAPPING a gift box

Builder = The gift box (wrapping around Person)
Person = The gift inside

operator Person() = "Open the box and give me the gift!"
```

---

## The = Sign — Constructor vs Assignment

### IMPORTANT: = Does NOT Always Mean Assignment!
```cpp
// INITIALIZATION (= means Constructor!)
Person p = Person::create().lives()...;
//     ^^^
//     p doesn't exist yet → Constructor called!
//     Move Constructor: Person(Person&& other)

// ASSIGNMENT (= means operator=)
Person p;                              // p already exists
p = Person::create().lives()...;       // NOW it's assignment!
//^^^
// p already exists → operator= called!
// Move Assignment: Person& operator=(Person&& other)
```

### Rule
```
Type variable = something;    → INITIALIZATION → Constructor
variable = something;         → ASSIGNMENT → operator=

int x = 5;        → Initialization (not assignment!)
x = 10;           → Assignment

Person p = ...;   → Move Constructor (initialization!)
p = ...;          → Move Assignment (p already exists!)
```

---

## What is std::move?
```
std::move does NOT actually move anything!
It just MARKS an object as "ready to be moved"

return std::move(person);

Step 1: std::move(person) → marks person as movable
Step 2: return → Move Constructor creates new Person from marked person
Step 3: Original person becomes EMPTY (data transferred)

Analogy:
  Without move: PHOTOCOPY a book (slow, two copies exist)
  With move:    GIVE the book (fast, book changes hands)
```

---

## What is friend class?
```cpp
class Person {
private:
    string street_address;    // PRIVATE!
    string company_name;      // PRIVATE!

    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;
};

// Builders need to SET private fields:
person.street_address = "123 London";  // Only works because friend!

// Without friend:
// ❌ COMPILE ERROR: street_address is private!
```

---

## Why Private Constructor in Person?
```cpp
class Person {
    Person() {}    // PRIVATE!
};

// ❌ Can't create Person directly:
Person p;                    // ERROR! Constructor is private!

// ✅ Only through builder:
Person p = Person::create(); // Works! create() is inside Person class!

// WHY?
// Forces everyone to use builder!
// Can't create half-built Person!
// Guarantees proper construction!
```

---

## return *this — Method Chaining
```cpp
Self& at(std::string street) {
    person.street_address = street;
    return *this;    // Returns the builder itself!
}

// this  = pointer to current object (&builder)
// *this = the current object itself (builder)
// return *this = "here, take me back, call me again!"

// Enables:
.at("London Road").with_postcode("SW1").in("London")

// Without return *this:
builder.at("London Road");     // Returns nothing
builder.with_postcode("SW1");  // Must repeat "builder." ❌
builder.in("London");

// With return *this:
builder.at("London Road").with_postcode("SW1").in("London");
// Clean chain! ✅
```

---

## How Builders Can Switch Between Each Other
```
All builders inherit from PersonBuilderBase
PersonBuilderBase has: lives() and works()

So ANY builder can call lives() or works():

PersonAddressBuilder → inherits lives() and works()
PersonJobBuilder     → inherits lives() and works()

Chain:
.lives()              → Returns AddressBuilder
    .at("London Road") → Returns AddressBuilder (chaining)
    .in("London")      → Returns AddressBuilder (chaining)
    .works()           → Returns JobBuilder (switch!)
        .at("Google")  → Returns JobBuilder (chaining)
        .earning(100)  → Returns JobBuilder (chaining)
    .lives()           → Can switch back! (switch!)
        .in("Paris")   → Returns AddressBuilder (chaining)

Can switch between builders ANYTIME because
all inherit from same base with lives() and works()!
```

---

## Project Structure
```
BuilderFacets/
├── main.cpp                        ← Demo usage
├── model/
│   ├── Person.h                    ← The complex object
│   └── Person.cpp                  ← Person::create()
└── builder/
    ├── PersonBuilderBase.h/.cpp    ← Base (has Person&, lives(), works())
    ├── PersonBuilder.h             ← OWNS Person, starts the chain
    ├── PersonAddressBuilder.h      ← Sets address fields
    └── PersonJobBuilder.h          ← Sets job fields
```

---

## Complete Chain Flow — One Picture
```
Person p = Person::create()
    .lives().at("123 London").in("London")
    .works().at("PragmaSoft").earning(100);

1. create()          → PersonBuilder created (OWNS Person p)
2. .lives()          → PersonAddressBuilder (REFERENCE to same p)
3. .at("123 London") → p.street = "123 London" → return *this
4. .in("London")     → p.city = "London" → return *this
5. .works()          → PersonJobBuilder (REFERENCE to same p)
6. .at("PragmaSoft") → p.company = "PragmaSoft" → return *this
7. .earning(100)     → p.income = 100 → return *this
8. Person p =        → Compiler calls operator Person()
                     → std::move(person)
                     → Move Constructor creates final Person
                     → p is complete! ✅
```

---

## Summary
```
┌──────────────────────────────────────────────────────────┐
│                                                          │
│  Builder Facets = Multiple builders for one object       │
│                                                          │
│  Only ONE Person exists — all builders share it          │
│  via Person& reference                                   │
│                                                          │
│  PersonBuilder      → OWNS Person (Person p)            │
│  AddressBuilder     → REFERENCES Person (Person& person)│
│  JobBuilder         → REFERENCES Person (Person& person)│
│                                                          │
│  operator Person()  → Converts builder to Person        │
│  return *this       → Enables method chaining           │
│  std::move          → Transfers ownership efficiently   │
│  friend class       → Lets builders access private fields│
│  Private constructor→ Forces builder usage               │
│                                                          │
│  Person p = ...     → Initialization (Constructor)      │
│  p = ...            → Assignment (operator=)            │
│                                                          │
└──────────────────────────────────────────────────────────┘
```
