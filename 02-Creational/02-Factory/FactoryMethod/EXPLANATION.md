# Factory Method Pattern

## What is Factory Pattern?

```
Factory Pattern = Separate object CREATION from object USE

Instead of:
  Point p(3, 4);           // Direct creation — hard to control

Use:
  Point p = PointFactory::NewCartesian(3, 4);  // Factory creates it
```

---

## The Problem Without Factory

### Confusing Constructor
```cpp
class Point {
public:
    Point(float a, float b, PointType type = PointType::cartesian) {
        if (type == PointType::cartesian) {
            x = a; 
            y = b;
        } else {  // polar
            x = a * cos(b);  // a = radius, b = angle
            y = a * sin(b);
        }
    }
};

// Usage:
Point p1(3, 4, PointType::cartesian);  // x=3, y=4
Point p2(5, 0.927, PointType::polar);  // What are these numbers??

// Problems:
// 1. Same constructor, DIFFERENT meanings for a,b
// 2. Easy to forget type parameter
// 3. Can't have two constructors with same signature
// 4. Not clear what 5 and 0.927 mean
```

### Can't Have Two Constructors
```cpp
// ❌ COMPILE ERROR — same signature!
Point(float x, float y);           // Cartesian
Point(float r, float theta);       // Polar
// Both take (float, float) — compiler can't tell difference!
```

---

## Solution: Factory Method

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

// Usage:
auto p1 = PointFactory::NewCartesian(3, 4);     // Clear! x=3, y=4
auto p2 = PointFactory::NewPolar(5, 0.927);     // Clear! radius=5, angle=0.927
```

---

## Benefits

```
1. CLEAR Intent
   NewCartesian(3, 4)  → Obvious: x=3, y=4
   NewPolar(5, 0.927)  → Obvious: r=5, θ=0.927

2. UNLIMITED factory methods
   NewCartesian()
   NewPolar()
   NewFromOrigin()
   NewFromTwoPoints()
   ... as many as you want!

3. CONTROLLED creation
   Point constructor is PRIVATE
   Can ONLY create through factory
   Factory can add validation, logging, caching, etc.

4. SEPARATE concerns
   Point = Stores x,y coordinates
   PointFactory = Knows HOW to create Points
```

---

## Why Private Constructor?

```cpp
class Point {
    Point(float x, float y) : x(x), y(y) {}  // PRIVATE!
    friend class PointFactory;
};

// ❌ Can't create Point directly:
Point p(3, 4);  // ERROR! Constructor is private!

// ✅ Must use factory:
auto p = PointFactory::NewCartesian(3, 4);

// WHY?
// 1. Forces everyone to use factory (consistency)
// 2. Factory can add logic (validation, logging)
// 3. Can't bypass factory and create invalid Points
```

---

## What is friend class?

```cpp
class Point {
private:
    float x, y;
    Point(float x, float y) : x(x), y(y) {}  // PRIVATE!

    friend class PointFactory;  // ← Grants access!
};

// PointFactory can access private members:
class PointFactory {
    static Point NewCartesian(float x, float y) {
        return Point{x, y};  // ✅ Can call private constructor!
    }
};

// Without friend:
// ❌ ERROR: Point::Point() is private!
```

```
friend class = Giving someone a KEY to your house
               They can access everything inside
               But they're NOT part of your family (not inheritance!)
```

---

## What is static?

```cpp
class PointFactory {
public:
    static Point NewCartesian(float x, float y);
    //     ^^^^^^
    //     static = belongs to CLASS, not to OBJECT
};

// ✅ Call without creating object:
auto p = PointFactory::NewCartesian(3, 4);
//       ^^^^^^^^^^^^^
//       Call on CLASS, not on object!

// vs Non-static (normal method):
PointFactory factory;           // Must create object first
auto p = factory.NewCartesian(3, 4);  // Call on object

// For factory methods, static makes sense:
// You don't need factory DATA (no member variables)
// You just need factory BEHAVIOR (create Points)
// So make it static — no need for useless object!
```

---

## Project Structure

```
FactoryMethod/
├── main.cpp              ← Demo usage
├── model/
│   ├── Point.h           ← The product (what factory creates)
│   └── Point.cpp
└── factory/
    ├── PointFactory.h    ← The factory (creates Points)
    └── PointFactory.cpp
```

---

## When to Use Factory Method

```
✅ USE when:
  Multiple ways to construct same object
  Constructor parameters are confusing
  Need to enforce creation rules
  Want to add creation logic (validation, logging)

❌ DON'T USE when:
  Simple object with one obvious constructor
  Point(x, y) is clear enough → no factory needed
```

---

## Summary

```
┌──────────────────────────────────────────────────────────┐
│                                                          │
│  Factory Method = Separate class creates objects         │
│                                                          │
│  Point             → Stores data (x, y)                  │
│  PointFactory      → Creates Points                      │
│                                                          │
│  Private constructor → Forces factory use                │
│  friend class       → Lets factory access private        │
│  static methods     → No factory object needed           │
│                                                          │
│  Benefits:                                               │
│    Clear intent                                          │
│    Unlimited creation methods                            │
│    Controlled creation                                   │
│    Separation of concerns                                │
│                                                          │
└──────────────────────────────────────────────────────────┘
```
