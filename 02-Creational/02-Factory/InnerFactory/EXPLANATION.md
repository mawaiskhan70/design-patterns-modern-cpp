# Inner Factory Pattern

## What is Inner Factory?

```
Inner Factory = Factory class INSIDE the product class

Regular Factory:
  Point         → Separate class
  PointFactory  → Separate class

Inner Factory:
  Point
  └── PointFactory  → NESTED inside Point!
```

---

## Code Structure

```cpp
class Point {
    float x, y;
    Point(float x, float y) : x(x), y(y) {}  // Private!

public:
    // Inner Factory — INSIDE Point class!
    class PointFactory {
    public:
        static Point NewCartesian(float x, float y) {
            return Point{x, y};  // Can access private constructor!
        }
        
        static Point NewPolar(float r, float theta) {
            return Point{r * cos(theta), r * sin(theta)};
        }
    };

    static PointFactory Factory;  // Singleton-style access
};

// Initialize static member
Point::PointFactory Point::Factory;
```

---

## How to Use It

```cpp
// Method 1: Through Point::Factory
auto p1 = Point::Factory.NewCartesian(3, 4);

// Method 2: Direct class access
auto p2 = Point::PointFactory::NewCartesian(3, 4);

// Both work! Factory object is optional (static methods)
```

---

## Inner vs Outer Factory

### Outer Factory (Separate Class)
```cpp
// Two separate classes
class Point { /* ... */ };
class PointFactory { /* ... */ };

// Usage:
auto p = PointFactory::NewCartesian(3, 4);
//       ^^^^^^^^^^^^^
//       Separate class name
```

### Inner Factory (Nested Class)
```cpp
// Factory INSIDE Point
class Point {
    class PointFactory { /* ... */ };
    static PointFactory Factory;
};

// Usage:
auto p = Point::Factory.NewCartesian(3, 4);
//       ^^^^^
//       Start with Point, then Factory
```

---

## Benefits of Inner Factory

```
1. ENCAPSULATION
   Factory is LOGICALLY part of Point
   Point::PointFactory clearly shows relationship

2. ACCESS to private members WITHOUT friend
   Inner class automatically has access to outer class private members!
   No need for friend keyword!

3. NAMESPACE organization
   Point::Factory — clearly belongs to Point
   vs PointFactory — separate, less clear

4. ONE file instead of two
   Point.h contains BOTH Point and Factory
   Easier to maintain
```

---

## Why Factory is Nested But Can Still Access Private?

```cpp
class Point {
    float x, y;
    Point(float x, float y) : x(x), y(y) {}  // Private!

    class PointFactory {
        static Point NewCartesian(float x, float y) {
            return Point{x, y};  // ✅ Can access! Why?
        }
    };
};

// RULE:
// Inner (nested) class has access to outer class private members!
// This is C++ rule — NO friend keyword needed!
```

---

## What is static PointFactory Factory?

```cpp
class Point {
    class PointFactory { /* ... */ };
    static PointFactory Factory;  // ← What's this?
};

// Initialize in .cpp file:
Point::PointFactory Point::Factory;

// This creates ONE shared Factory object for ALL Points
// Like a singleton — everyone uses SAME factory

// Usage:
Point::Factory.NewCartesian(3, 4);
//     ^^^^^^^
//     ONE shared factory object
```

```
static Factory = Like having ONE shared vending machine
                 for the whole building
                 Everyone uses SAME machine
                 Don't need to create your own!
```

---

## With vs Without static Factory

```cpp
// WITHOUT static Factory member:
class Point {
    class PointFactory { /* ... */ };
};

// Usage — long name:
auto p = Point::PointFactory::NewCartesian(3, 4);
//       ^^^^^^^^^^^^^^^^^^^^
//       Long, but clear


// WITH static Factory member:
class Point {
    class PointFactory { /* ... */ };
    static PointFactory Factory;
};

// Usage — shorter:
auto p = Point::Factory.NewCartesian(3, 4);
//       ^^^^^^^^^^^^^^
//       Shorter, cleaner
```

---

## Private Constructor in Inner Factory

```cpp
class PointFactory {
    PointFactory() {}  // Private constructor — why?
public:
    static Point NewCartesian(...);
};

// WHY private constructor?
// Because ALL methods are static!
// Don't need to create factory objects!

// ❌ Prevents useless creation:
Point::PointFactory pf;  // Compiles but WHY create this??

// ✅ Just use static methods:
Point::Factory.NewCartesian(3, 4);  // No object needed!
```

---

## Project Structure

```
InnerFactory/
├── main.cpp
└── model/
    ├── Point.h      ← Contains BOTH Point and PointFactory
    └── Point.cpp
```

---

## Inner Factory vs Outer Factory — When to Use

```
┌────────────────────────┬──────────────────┬──────────────────┐
│ Feature                │ Outer Factory    │ Inner Factory    │
├────────────────────────┼──────────────────┼──────────────────┤
│ Number of files        │ More (2+ files)  │ Fewer (1-2 files)│
│ Namespace clarity      │ OK               │ Better           │
│ Encapsulation          │ Good             │ Better           │
│ Need friend?           │ Yes              │ No               │
│ Access to private      │ Via friend       │ Automatic        │
│ Usage syntax           │ Factory::New()   │ Point::Factory   │
│ When to use            │ Complex factory  │ Simple factory   │
│                        │ Shared by many   │ Tight coupling   │
└────────────────────────┴──────────────────┴──────────────────┘
```

```
Use Inner Factory when:
  ✅ Factory is ONLY used for this ONE class
  ✅ Want to keep everything in ONE place
  ✅ Small, simple factory

Use Outer Factory when:
  ✅ Factory creates MULTIPLE types
  ✅ Factory is complex with lots of logic
  ✅ Factory might be reused elsewhere
```

---

## Summary

```
┌──────────────────────────────────────────────────────────┐
│                                                          │
│  Inner Factory = Factory nested INSIDE product class     │
│                                                          │
│  class Point {                                           │
│      class PointFactory { ... }  ← Inner class           │
│      static PointFactory Factory;                        │
│  };                                                      │
│                                                          │
│  Benefits:                                               │
│    Better encapsulation                                  │
│    Auto access to private (no friend needed)             │
│    Clearer relationship (Point::Factory)                 │
│    Fewer files to manage                                 │
│                                                          │
│  Trade-off:                                              │
│    Less flexible if factory needs to create many types   │
│                                                          │
│  Use when: Factory is tightly coupled to ONE class       │
│                                                          │
└──────────────────────────────────────────────────────────┘
```
