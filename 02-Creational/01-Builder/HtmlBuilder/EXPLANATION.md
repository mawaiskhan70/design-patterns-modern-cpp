# Builder Pattern — Groovy Style HTML

## Definition
> Separate the construction of a complex object from its representation
> so that the same construction process can create different representations.

---

## Why Builder Pattern?

### Problem: Complex Object Construction
```cpp
// ❌ Building HTML with raw strings — messy and error-prone
string html = "<ul><li>Item 1</li><li>Item 2</li></ul>";

// ❌ Easy to forget closing tags
// ❌ Hard to read
// ❌ No validation
// ❌ No structure
```

### Solution: Builder Pattern
```cpp
// ✅ Method 1: Groovy Style — clean, readable (One WAY to implement builder pattern)
P {
    IMG {"http://pokemon.com/pikachu.png"}
}

// ✅ Method 2: Builder — step by step
HtmlBuilder("ul")
    .addChild("li", "Item 1")
    .addChild("li", "Item 2")
    .addChild("li", "Item 3");
```

---

## Two Approaches in This Project

### 1. Groovy Style (Direct Construction)
```
Uses: Constructors + initializer_list + operator<<
Good for: Known structure at compile time
```

### 2. Builder Pattern (Step by Step)
```
Uses: Builder class with fluent API (method chaining)
Good for: Dynamic construction at runtime
```

---

## Key Concepts

### Protected Constructors
```
Tag constructors are PROTECTED
→ Can't create Tag directly: Tag t("div",""); ❌
→ Only child classes can: P p("text"); ✅
→ Forces use of specific tag types (P, IMG, etc.)
```

### Friend operator<<
```
friend ostream& operator<<(ostream& os, const Tag& tag)
→ Teaches cout HOW to print Tag objects
→ cout << myTag; // Works!
→ Recursive: prints children automatically
```

### initializer_list
```
P(initializer_list<Tag> children)
→ Allows: P { IMG{"url1"}, IMG{"url2"} }
→ Creates list of Tags from {}
→ Groovy-style syntax
```

### Method Chaining (Fluent API)
```cpp
builder.addChild("li", "Item 1")    // returns *this
       .addChild("li", "Item 2")    // returns *this
       .addChild("li", "Item 3");   // returns *this

// Each method returns reference to builder itself
// So you can chain calls!
```

### Self-Closing Tags
```
No children + No text → <img src="url"/>
Has children or text  → <p>...</p>
```

---

## Project Structure
```
HtmlBuilder/
├── main.cpp              ← Demo both approaches
├── tags/
│   ├── Tag.h / .cpp      ← Base tag (protected constructors)
│   ├── P.h / .cpp        ← <p> tag
│   └── IMG.h / .cpp      ← <img> tag
└── builder/
    └── HtmlBuilder.h/.cpp ← Builder pattern implementation
```

---

## Summary
```
Builder Pattern = Construct complex objects step by step
Groovy Style    = Use C++ syntax to look like the output
Both avoid raw string manipulation
Both provide clean, readable, maintainable code
```
