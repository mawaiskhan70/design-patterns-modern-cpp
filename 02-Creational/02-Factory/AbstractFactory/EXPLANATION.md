# Abstract Factory Pattern

## What is Abstract Factory?

```
Abstract Factory = Factory of Factories!

Regular Factory:
  PointFactory creates Points

Abstract Factory:
  DrinkFactory creates Drinks
    ├── Can create Tea (via TeaFactory)
    ├── Can create Coffee (via CoffeeFactory)
    └── Can create more drinks by adding factories!
```

---

## The Problem — Without Abstract Factory

```cpp
// ❌ Manual creation with if-else — BAD!
unique_ptr<HotDrink> make_drink(string type) {
    unique_ptr<HotDrink> drink;
    
    if (type == "tea") {
        drink = make_unique<Tea>();
        drink->prepare(200);
    } else if (type == "coffee") {
        drink = make_unique<Coffee>();
        drink->prepare(50);
    } else if (type == "hot_chocolate") {  // New drink added
        drink = make_unique<HotChocolate>();
        drink->prepare(150);
    } // ... more else-if for each new drink!
    
    return drink;
}

// Problems:
// 1. Must MODIFY function for each new drink (violates OCP!)
// 2. Preparation logic mixed with creation logic
// 3. Volume hardcoded — can't customize
// 4. If-else chain gets HUGE with many drinks
```

---

## Solution — Abstract Factory

### Step 1: Product Hierarchy (What We Create)

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
        cout << "Take tea bag, boil water, pour " 
             << volume << "ml, add lemon" << endl;
    }
};

class Coffee : public HotDrink {
    void prepare(int volume) override {
        cout << "Grind beans, boil water, pour " 
             << volume << "ml, add cream" << endl;
    }
};
```

### Step 2: Factory Hierarchy (How We Create)

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

### Step 3: Main Factory (Factory of Factories!)

```cpp
class DrinkFactory {
    map<string, unique_ptr<HotDrinkFactory>> hot_factories;

public:
    DrinkFactory() {
        // Register all drink factories
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

### Step 4: Usage

```cpp
DrinkFactory df;
auto tea = df.make_drink("tea");       // Creates Tea via TeaFactory
auto coffee = df.make_drink("coffee"); // Creates Coffee via CoffeeFactory
```

---

## How It Works — Step by Step

```
User: "I want tea"
│
▼
DrinkFactory::make_drink("tea")
│
├── Look up "tea" in hot_factories map
│   └── Finds TeaFactory
│
├── Call TeaFactory->make()
│   └── Creates Tea object
│
├── Call tea->prepare(200)
│   └── "Take tea bag, boil water, pour 200ml..."
│
└── Return tea to user ✅
```

---

## Why "Abstract" Factory?

```
"Abstract" = Uses interfaces/base classes

HotDrinkFactory is ABSTRACT (pure virtual = 0)
TeaFactory, CoffeeFactory are CONCRETE

DrinkFactory doesn't know WHICH concrete factory it uses
It just knows they ALL implement make()

This is POLYMORPHISM at the factory level!
```

---

## Adding New Drink — See The Power!

```cpp
// Step 1: Add new product
class HotChocolate : public HotDrink {
    void prepare(int volume) override {
        cout << "Heat milk, add chocolate, pour " 
             << volume << "ml" << endl;
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
    hot_factories["chocolate"] = make_unique<HotChocolateFactory>();  // NEW!
}

// Step 4: Use it!
auto choc = df.make_drink("chocolate");  // Works! ✅

// DrinkFactory class itself UNCHANGED!
// Just added ONE line in constructor!
// This is Open/Closed Principle! 🎯
```

---

## What is unique_ptr?

```cpp
unique_ptr<HotDrink> drink = make_unique<Tea>();

// unique_ptr = Smart pointer that OWNS an object
//              Automatically DELETES when out of scope
//              No memory leaks!

// Without unique_ptr (old C++ way):
HotDrink* drink = new Tea();  // Manual allocation
delete drink;                  // Must remember to delete! Easy to forget!

// With unique_ptr:
unique_ptr<HotDrink> drink = make_unique<Tea>();
// Automatically deleted when drink goes out of scope! ✅
// No memory leaks even if exception thrown!
```

```
unique_ptr = You OWN the object exclusively
             Only ONE owner at a time
             Can't copy, can only move
             
Like owning a CAR:
  Only ONE person owns it
  Can transfer ownership (move)
  But can't duplicate the car!
```

---

## What is map<string, unique_ptr<Factory>>?

```cpp
map<string, unique_ptr<HotDrinkFactory>> hot_factories;

// map = Dictionary/Hashtable
//       Key → Value

hot_factories["tea"]    → TeaFactory object
hot_factories["coffee"] → CoffeeFactory object

// Like a phone book:
// "John"   → 555-1234
// "Jane"   → 555-5678

// Access by key:
auto factory = hot_factories["tea"];   // Gets TeaFactory
auto drink = factory->make();          // Creates Tea
```

---

## Why Store Factories in map?

```cpp
// ❌ Without map — need if-else:
if (name == "tea") return TeaFactory().make();
else if (name == "coffee") return CoffeeFactory().make();
else if ...  // Endless chain!

// ✅ With map — lookup!
return hot_factories[name]->make();  // ONE line! Any drink!
```

---

## Class Hierarchy Diagram

```
Products:
    HotDrink (interface)
    ├── Tea
    ├── Coffee
    └── HotChocolate

Factories:
    HotDrinkFactory (interface)
    ├── TeaFactory      → creates Tea
    ├── CoffeeFactory   → creates Coffee
    └── HotChocolateFactory → creates HotChocolate

Main Factory:
    DrinkFactory
    └── Contains map of all HotDrinkFactory implementations
        └── Delegates creation to appropriate factory
```

---

## Project Structure

```
AbstractFactory/
├── main.cpp
├── drinks/
│   ├── HotDrink.h      ← Base product interface
│   ├── Tea.h/.cpp      ← Concrete product
│   └── Coffee.h/.cpp   ← Concrete product
└── factories/
    ├── HotDrinkFactory.h    ← Base factory interface
    ├── TeaFactory.h         ← Concrete factory (header-only)
    ├── CoffeeFactory.h      ← Concrete factory (header-only)
    ├── DrinkFactory.h/.cpp  ← Main factory (factory of factories)
```

---

## When to Use Abstract Factory

```
✅ USE when:
  Need to create FAMILIES of related objects
  (Tea, Coffee, HotChocolate are all HotDrinks)
  
  Want to add new types WITHOUT modifying existing code
  (Open/Closed Principle)
  
  Creation logic is complex and needs hierarchy
  
  Runtime decision on which type to create

❌ DON'T USE when:
  Only ONE or TWO types to create (overkill!)
  Simple factory method is enough
  Types don't form a family
```

---

## Summary

```
┌──────────────────────────────────────────────────────────┐
│                                                          │
│  Abstract Factory = Factory that creates other factories │
│                                                          │
│  Structure:                                              │
│    Product hierarchy    (HotDrink → Tea, Coffee)         │
│    Factory hierarchy    (HotDrinkFactory → TeaFactory)   │
│    Main factory         (DrinkFactory manages all)       │
│                                                          │
│  Benefits:                                               │
│    No if-else chains                                     │
│    Easy to add new types (just add factory)              │
│    Follows Open/Closed Principle                         │
│    Centralized creation logic                            │
│                                                          │
│  Key Concepts:                                           │
│    unique_ptr = Auto memory management                   │
│    map = Key-value storage                               │
│    Polymorphism = Base class pointer to child objects    │
│                                                          │
└──────────────────────────────────────────────────────────┘
```
