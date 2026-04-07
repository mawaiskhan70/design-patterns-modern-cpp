# 📝 Factory Pattern — Complete Revision Notes

## What is Factory Pattern?

```
Factory Pattern = Separate object CREATION from object USE

Instead of creating objects directly with constructors,
delegate creation to a FACTORY that knows HOW to create them.

WHY?
  Constructors are limited (same signature issues)
  Creation logic might be complex
  Want to control and centralize object creation
```

---

## The Three Types of Factory Patterns

```
┌─────────────────────────────────────────────────────────┐
│                                                         │
│  1. Factory Method    → Separate factory class          │
│  2. Inner Factory     → Factory inside product class    │
│  3. Abstract Factory  → Factory of factories            │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

---

## 1. Factory Method Pattern

### Problem It Solves
```cpp
// ❌ Can't have multiple constructors with same signature
class Point {
    Point(float x, float y);       // Cartesian
    Point(float r, float theta);   // Polar — ERROR! Same signature!
};

// ❌ Confusing single constructor
Point p(5, 0.927, PointType::polar);  // What are these numbers??
```

### Solution
```cpp
class Point {
    float x, y;
    Point(float x, float y) : x(x), y(y) {}  // Private!
    friend class PointFactory;
};

class PointFactory {
public:
    static Point NewCartesian(float x, float y) {
        return Point{x, y};
    }
    
    static Point NewPolar(float r, float theta) {
        return Point{r * cos(theta), r * sin(theta)};
    }
};

// Usage — CLEAR intent:
auto p1 = PointFactory::NewCartesian(3, 4);
auto p2 = PointFactory::NewPolar(5, 0.927);
```

### Key Concepts

#### Private Constructor
```
Point(float x, float y) {}  // PRIVATE!

WHY?
  Forces users to use factory
  Can't bypass factory and create invalid Points
  Centralized control over object creation
```

#### friend class
```cpp
friend class PointFactory;

Gives PointFactory ACCESS to Point's private members
Like giving someone a KEY to your house

Without friend:
  ❌ PointFactory can't call private Point constructor
```

#### static methods
```cpp
static Point NewCartesian(float x, float y);

static = Belongs to CLASS, not to OBJECT
Can call WITHOUT creating factory object

PointFactory::NewCartesian(3, 4);  ← No object needed!

vs non-static:
  PointFactory pf;                 ← Must create object first
  pf.NewCartesian(3, 4);           ← Call on object
```

### Structure
```
Point           → Product (what's created)
PointFactory    → Factory (creates products)
  TWO separate classes
  TWO separate files
```

### When to Use
```
✅ Multiple ways to create same object
✅ Constructor parameters are confusing  
✅ Need controlled/validated creation
✅ Want clear, named creation methods

❌ Simple object with obvious constructor
```

---

## 2. Inner Factory Pattern

### Difference from Factory Method
```
Factory Method:  Point and PointFactory are SEPARATE classes
Inner Factory:   PointFactory is INSIDE Point class
```

### Code
```cpp
class Point {
    float x, y;
    Point(float x, float y) : x(x), y(y) {}  // Private!

public:
    // Inner Factory — NESTED class
    class PointFactory {
    public:
        static Point NewCartesian(float x, float y) {
            return Point{x, y};  // Can access private! (inner class privilege)
        }
        
        static Point NewPolar(float r, float theta) {
            return Point{r * cos(theta), r * sin(theta)};
        }
    };

    // Optional: Singleton-style access
    static PointFactory Factory;
};

// In .cpp file:
Point::PointFactory Point::Factory;
```

### Usage — TWO Ways
```cpp
// Method 1: Through Factory object
auto p1 = Point::Factory.NewCartesian(3, 4);

// Method 2: Direct class access
auto p2 = Point::PointFactory::NewCartesian(3, 4);

// Both work! (because methods are static)
```

### Key Difference from Outer Factory
```
┌────────────────────┬──────────────────┬──────────────────┐
│                    │ Outer Factory    │ Inner Factory    │
├────────────────────┼──────────────────┼──────────────────┤
│ Files              │ 2 separate       │ 1 file           │
│ Need friend?       │ ✅ Yes           │ ❌ No (automatic)│
│ Encapsulation      │ Good             │ Better           │
│ Syntax             │ Factory::New()   │ Point::Factory   │
│ Relationship shown?│ Less clear       │ Very clear       │
└────────────────────┴──────────────────┴──────────────────┘
```

### Why Inner Class Can Access Private?
```
C++ RULE:
Inner (nested) class automatically has access to 
outer class private members — NO friend keyword needed!

This is a language feature, not something you enable.
```

### static PointFactory Factory
```cpp
static PointFactory Factory;

Creates ONE shared factory object for ALL Points
Like a vending machine everyone uses

Benefit: Shorter syntax
  Point::Factory.NewCartesian(3, 4)
vs
  Point::PointFactory::NewCartesian(3, 4)
```

### When to Use
```
✅ Factory ONLY creates this ONE class
✅ Want everything in ONE file
✅ Small, simple factory
✅ Want to show tight relationship

❌ Factory creates MULTIPLE different types
❌ Complex factory with lots of logic
```

---

## 3. Abstract Factory Pattern

### What is it?
```
Abstract Factory = Factory of Factories!

Instead of one factory creating one type,
you have a HIERARCHY of factories creating
a FAMILY of related objects.
```

### Problem It Solves
```cpp
// ❌ Manual if-else — violates Open/Closed Principle
unique_ptr<HotDrink> make_drink(string type) {
    if (type == "tea") {
        auto drink = make_unique<Tea>();
        drink->prepare(200);
        return drink;
    } else if (type == "coffee") {
        auto drink = make_unique<Coffee>();
        drink->prepare(50);
        return drink;
    }
    // Add new drink? MODIFY this function! ❌
}
```

### Solution — Three-Level Hierarchy

#### Level 1: Product Hierarchy
```cpp
// Base interface
class HotDrink {
public:
    virtual ~HotDrink() = default;
    virtual void prepare(int volume) = 0;
};

// Concrete products
class Tea : public HotDrink {
    void prepare(int volume) override {
        cout << "Prepare tea with " << volume << "ml water" << endl;
    }
};

class Coffee : public HotDrink {
    void prepare(int volume) override {
        cout << "Prepare coffee with " << volume << "ml water" << endl;
    }
};
```

#### Level 2: Factory Hierarchy
```cpp
// Abstract factory interface
class HotDrinkFactory {
public:
    virtual ~HotDrinkFactory() = default;
    virtual unique_ptr<HotDrink> make() const = 0;
};

// Concrete factories
class TeaFactory : public HotDrinkFactory {
    unique_ptr<HotDrink> make() const override {
        return make_unique<Tea>();
    }
};

class CoffeeFactory : public HotDrinkFactory {
    unique_ptr<HotDrink> make() const override {
        return make_unique<Coffee>();
    }
};
```

#### Level 3: Main Factory (Factory of Factories)
```cpp
class DrinkFactory {
    map<string, unique_ptr<HotDrinkFactory>> hot_factories;

public:
    DrinkFactory() {
        // Register all factories
        hot_factories["tea"] = make_unique<TeaFactory>();
        hot_factories["coffee"] = make_unique<CoffeeFactory>();
    }

    unique_ptr<HotDrink> make_drink(const string& name) {
        auto drink = hot_factories[name]->make();
        drink->prepare(200);
        return drink;
    }
};
```

### Usage
```cpp
DrinkFactory df;
auto tea = df.make_drink("tea");       // TeaFactory creates Tea
auto coffee = df.make_drink("coffee"); // CoffeeFactory creates Coffee
```

### How It Works — Flow
```
User calls: df.make_drink("tea")
│
├─ DrinkFactory looks up "tea" in map
│   └─ Finds: TeaFactory
│
├─ Calls: TeaFactory->make()
│   └─ Creates: Tea object
│
├─ Calls: tea->prepare(200)
│   └─ Executes: "Prepare tea with 200ml water"
│
└─ Returns: unique_ptr<HotDrink> pointing to Tea
```

### Key Concepts

#### unique_ptr
```cpp
unique_ptr<HotDrink> drink = make_unique<Tea>();

Smart pointer that OWNS an object
Automatically DELETES when out of scope
No memory leaks!

vs old C++ way:
HotDrink* drink = new Tea();    // Manual allocation
delete drink;                    // Must remember! Easy to forget!

unique_ptr Rules:
  ✅ Exclusive ownership (only ONE owner)
  ✅ Can't copy (only move)
  ✅ Auto-deletes
  
Like owning a car:
  Only ONE person owns it
  Can transfer ownership
  Can't duplicate the car
```

#### map<string, unique_ptr<Factory>>
```cpp
map<string, unique_ptr<HotDrinkFactory>> hot_factories;

Dictionary / Hash table
Key (string) → Value (Factory pointer)

hot_factories["tea"]    → TeaFactory
hot_factories["coffee"] → CoffeeFactory

Like a phone book:
"Alice" → 555-1234
"Bob"   → 555-5678

Access:
auto factory = hot_factories["tea"];
auto drink = factory->make();
```

#### Why Abstract?
```
"Abstract" = Uses interfaces/base classes

HotDrinkFactory is ABSTRACT (has pure virtual = 0)
TeaFactory, CoffeeFactory are CONCRETE

DrinkFactory doesn't know WHICH concrete factory
It just knows ALL factories have make() method

This is POLYMORPHISM at factory level!
```

### Adding New Drink — Power of Abstract Factory
```cpp
// Step 1: Add new product
class HotChocolate : public HotDrink {
    void prepare(int volume) override {
        cout << "Prepare chocolate with " << volume << "ml" << endl;
    }
};

// Step 2: Add new factory
class HotChocolateFactory : public HotDrinkFactory {
    unique_ptr<HotDrink> make() const override {
        return make_unique<HotChocolate>();
    }
};

// Step 3: Register in DrinkFactory constructor
DrinkFactory() {
    hot_factories["tea"] = make_unique<TeaFactory>();
    hot_factories["coffee"] = make_unique<CoffeeFactory>();
    hot_factories["chocolate"] = make_unique<HotChocolateFactory>(); // NEW!
}

// DrinkFactory class code? UNCHANGED!
// Just ONE line added in constructor!
// This is Open/Closed Principle! 🎯
```

### When to Use
```
✅ Family of related objects (Tea, Coffee, Chocolate are all HotDrinks)
✅ Need to add types without modifying existing code
✅ Complex creation logic with hierarchy
✅ Runtime decision on which type to create

❌ Only 1-2 types (overkill!)
❌ Simple creation (use Factory Method instead)
```

---

## Comparison — All Three Factories

```
┌────────────────────┬─────────────────┬─────────────────┬──────────────────┐
│                    │ Factory Method  │ Inner Factory   │ Abstract Factory │
├────────────────────┼─────────────────┼─────────────────┼──────────────────┤
│ Complexity         │ Simple          │ Simple          │ Complex          │
├────────────────────┼─────────────────┼─────────────────┼──────────────────┤
│ Files needed       │ 2+ files        │ 1-2 files       │ Many files       │
├────────────────────┼─────────────────┼─────────────────┼──────────────────┤
│ Hierarchy          │ Flat            │ Flat            │ Multi-level      │
├────────────────────┼─────────────────┼─────────────────┼──────────────────┤
│ Creates            │ One type        │ One type        │ Family of types  │
├────────────────────┼─────────────────┼─────────────────┼──────────────────┤
│ Extensibility      │ Medium          │ Medium          │ High             │
├────────────────────┼─────────────────┼─────────────────┼──────────────────┤
│ Use case           │ Multiple ways   │ Tight coupling  │ Multiple product │
│                    │ to create Point │ to one class    │ families         │
├────────────────────┼─────────────────┼─────────────────┼──────────────────┤
│ Example            │ Point factories │ Point::Factory  │ Drink factories  │
└────────────────────┴─────────────────┴─────────────────┴──────────────────┘
```

---

## Key C++ Concepts Used

### 1. friend class
```
Grants another class access to private members
Like giving someone a key to your house

friend class PointFactory;

PointFactory can now access Point's private constructor
```

### 2. static keyword
```
static = Belongs to CLASS, not OBJECT

Static method:  Call on class, no object needed
Static member:  Shared by all instances

PointFactory::NewCartesian(3, 4);  ← No object!
```

### 3. Nested (Inner) Class
```
Class defined INSIDE another class
Automatically has access to outer class private members

class Outer {
    class Inner {
        // Can access Outer's private!
    };
};
```

### 4. unique_ptr
```
Smart pointer with exclusive ownership
Auto-deletes when out of scope
Can't copy, only move

unique_ptr<Tea> tea = make_unique<Tea>();
// No delete needed — automatic cleanup!
```

### 5. map (Dictionary)
```
Key-Value container
Fast lookup by key

map<string, int> ages;
ages["Alice"] = 25;
int age = ages["Alice"];  // 25
```

### 6. Pure Virtual Function
```
virtual void prepare(int volume) = 0;
                                   ^^^
                                   Makes class ABSTRACT
                                   MUST be implemented by children
```

---

## When to Use Which Pattern?

```
┌──────────────────────────────────────────────────────────────┐
│                                                              │
│  Need CLEAR creation methods?                                │
│  (NewCartesian vs NewPolar)                                  │
│    → Factory Method ✅                                       │
│                                                              │
│  Factory only for ONE class? Want tight coupling?            │
│    → Inner Factory ✅                                        │
│                                                              │
│  Multiple FAMILIES of related objects?                       │
│  Want to add types WITHOUT modifying code?                   │
│    → Abstract Factory ✅                                     │
│                                                              │
│  Simple object, obvious constructor?                         │
│    → NO factory needed! Just use constructor                 │
│                                                              │
└──────────────────────────────────────────────────────────────┘
```

---

## Common Mistakes to Avoid

```
❌ Using factory for SIMPLE objects
   Point(x, y) is clear? No factory needed!

❌ Making factory INSTANCE when methods are static
   PointFactory pf;  // Why? Just call PointFactory::New()

❌ Forgetting friend keyword (outer factory)
   Factory can't access private constructor!

❌ Not making base factory destructors virtual
   virtual ~HotDrinkFactory() = default;  ← IMPORTANT!

❌ Using raw pointers instead of unique_ptr
   new Tea();  ← Manual delete needed, memory leaks possible!
```

---

## Benefits of Factory Pattern (All Types)

```
✅ Separation of Concerns
   Creation logic ≠ Business logic

✅ Clear Intent
   NewCartesian(x,y) vs Point(x,y,type) — which is clearer?

✅ Flexibility
   Can add new creation methods without changing class

✅ Controlled Creation
   Validation, logging, caching all in one place

✅ Open/Closed Principle (especially Abstract Factory)
   Open for extension, closed for modification
```

---

## Quick Decision Guide

```
START: Need to create objects?
│
├─ Simple, obvious constructor? → Use constructor directly ✅
│
├─ Multiple ways to create same type?
│   ├─ Just 2-3 ways? → Factory Method ✅
│   └─ Tightly coupled to class? → Inner Factory ✅
│
└─ Multiple FAMILIES of related types?
    └─ Abstract Factory ✅
```

---

## Summary Cheat Sheet

```
┌──────────────────────────────────────────────────────────────┐
│                                                              │
│  FACTORY METHOD                                              │
│    Separate class creates objects                            │
│    PointFactory::NewCartesian()                              │
│    friend class needed                                       │
│                                                              │
│  INNER FACTORY                                               │
│    Nested class inside product                               │
│    Point::Factory.NewCartesian()                             │
│    No friend needed (automatic access)                       │
│                                                              │
│  ABSTRACT FACTORY                                            │
│    Hierarchy of factories creating hierarchy of products     │
│    DrinkFactory contains TeaFactory, CoffeeFactory           │
│    Easy to extend with new types                             │
│                                                              │
│  Key Concepts:                                               │
│    friend class    = Grant access to private                 │
│    static          = Belongs to class, not object            │
│    unique_ptr      = Smart pointer, auto-delete              │
│    map             = Key-value storage                       │
│    Pure virtual    = Must override (= 0)                     │
│                                                              │
└──────────────────────────────────────────────────────────────┘
```

---
