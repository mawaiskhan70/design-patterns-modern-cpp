````markdown
# Interface Segregation Principle (ISP) — Document Machine

## Definition
> Clients should NOT be forced to depend on interfaces they don't use.
> Many small, specific interfaces are better than one large, general interface.

---

## The Problem — Fat Interface

```
❌ BAD: One big interface forces ALL methods on EVERY class

IMachine
├── print()    ← Simple Printer FORCED to implement
├── scan()     ← Simple Printer FORCED to implement
└── fax()      ← Simple Printer FORCED to implement

class Printer : public IMachine {
    void print(Document& doc) override { /* OK */ }
    void scan(Document& doc) override  { /* EMPTY! Can't scan! */ }
    void fax(Document& doc) override   { /* EMPTY! Can't fax! */ }
};

Problems:
  1. Printer has EMPTY methods — meaningless code
  2. If IMachine adds new method → ALL classes must update
  3. Caller gets scan/fax on Printer — misleading!
  4. 2 criteria functions = 3 implementations
     3 criteria = 7 implementations
     N criteria = 2^N - 1 implementations! 💥
```

---

## The Solution — Segregated Interfaces

```
✅ GOOD: Small, focused interfaces

IPrinter              IScanner              IFax
└── print()           └── scan()            └── fax()

Printer  → implements ONLY IPrinter  ✅ (prints only)
Scanner  → implements ONLY IScanner  ✅ (scans only)
Machine  → implements IPrinter + IScanner ✅ (does both)

Each class implements ONLY what it CAN do!
No empty methods! No unnecessary dependencies!
```

---

## Project Structure

```
DocumentMachine/
├── main.cpp
├── model/
│   ├── document.h              ← Data model
│   └── document.cpp
├── interfaces/
│   ├── IPrinter.h              ← Small interface (CLOSED)
│   ├── IScanner.h              ← Small interface (CLOSED)
│   └── IMachine.h              ← Combined interface (CLOSED)
└── machines/
    ├── Printer.h / .cpp        ← Implements ONLY IPrinter
    ├── Scanner.h / .cpp        ← Implements ONLY IScanner
    └── Machine.h / .cpp        ← Implements BOTH via delegation
```

---

## How Interfaces Are Designed

### Small, Focused Interfaces

```cpp
// ONLY printing — nothing else!
class IPrinter {
    virtual void print(Document& doc) = 0;
};

// ONLY scanning — nothing else!
class IScanner {
    virtual void scan(Document& doc) = 0;
};
```

### Combined Interface (When Needed)

```cpp
// For devices that CAN do both
class IMachine : public IPrinter, public IScanner {};

// Inherits BOTH interfaces
// Only used by multi-function devices
```

---

## Implementations

### Printer — Only Prints

```cpp
class Printer : public IPrinter {
    // No scan! No fax! Only what it CAN do!
    void print(Document& doc) override;
};
```

### Scanner — Only Scans

```cpp
class Scanner : public IScanner {
    // No print! No fax! Only what it CAN do!
    void scan(Document& doc) override;
};
```

### Machine — Does Both via Delegation

```cpp
class Machine : public IMachine {
    IPrinter& printer;    // Reference to ANY printer
    IScanner& scanner;    // Reference to ANY scanner

    Machine(IPrinter& printer, IScanner& scanner);

    void print(Document& doc) override {
        printer.print(doc);   // Delegates to actual printer
    }
    void scan(Document& doc) override {
        scanner.scan(doc);    // Delegates to actual scanner
    }
};
```

---

## Key Concept: Why IPrinter& Not Printer&?

```
Machine takes IPrinter& (interface reference) because:

❌ Printer& printer      → Only accepts Printer class
                          → Can't use LaserPrinter, InkjetPrinter
                          → Must change Machine for new printers

✅ IPrinter& printer     → Accepts ANY class that implements IPrinter
                          → Printer, LaserPrinter, InkjetPrinter...
                          → Machine NEVER changes!

This is POLYMORPHISM:
  "Program to INTERFACE, not IMPLEMENTATION"
```

### How It Works In Memory

```
Printer printer;                    ← Actual object
IPrinter& ref = printer;           ← Reference to it

ref.print(doc);                    ← Calls Printer::print()
                                     Because ref POINTS to Printer object!

LaserPrinter laser;                ← Different actual object
IPrinter& ref2 = laser;           ← Reference to it

ref2.print(doc);                   ← Calls LaserPrinter::print()
                                     Because ref2 POINTS to LaserPrinter!

Same reference type (IPrinter&), different behavior!
This is POLYMORPHISM! 🎯
```

---

## Delegation Pattern

```
Machine doesn't implement print/scan itself!
It DELEGATES to actual Printer and Scanner objects.

Why?
  → Reuses existing Printer/Scanner code
  → No code duplication
  → Swappable at runtime

Machine machine(normalPrinter, scanner);   // Normal printing
Machine machine(laserPrinter, scanner);    // Laser printing
Machine machine(inkjetPrinter, scanner);   // Inkjet printing

Same Machine class, different behavior!
Just pass different implementations!
```

---

## Functions Accept Only What They Need

```cpp
// ✅ Takes ONLY IPrinter — doesn't know about scanning
void printDocument(IPrinter& printer, Document& doc) {
    printer.print(doc);
}

// ✅ Takes ONLY IScanner — doesn't know about printing
void scanDocument(IScanner& scanner, Document& doc) {
    scanner.scan(doc);
}

// Usage:
Printer printer;
Scanner scanner;
Machine machine(printer, scanner);

printDocument(printer, doc);    // ✅ Simple printer
printDocument(machine, doc);    // ✅ Machine works too!
scanDocument(scanner, doc);     // ✅ Simple scanner
scanDocument(machine, doc);     // ✅ Machine works too!

// printDocument doesn't care if it's Printer or Machine
// It only cares that it CAN print (implements IPrinter)
```

---

## Adding New Feature — ISP Makes It Easy

### Want to add Fax capability?

```
Step 1: Create small interface
   IFax { virtual void fax(Document& doc) = 0; }

Step 2: Create implementation
   FaxMachine : public IFax { void fax(doc) override; }

Step 3: Update IMachine if needed
   IMachine : IPrinter, IScanner, IFax {}

NOTHING existing changes!
  ✅ IPrinter unchanged
  ✅ IScanner unchanged
  ✅ Printer unchanged
  ✅ Scanner unchanged
  ✅ printDocument() unchanged
  ✅ scanDocument() unchanged
```

---

## No Constructor — Why?

```
Printer and Scanner have NO constructor because:
  → No member variables
  → Nothing to initialize
  → Compiler provides default constructor automatically
  → Writing empty constructor = unnecessary code

Machine HAS constructor because:
  → Has IPrinter& and IScanner& members
  → References MUST be initialized
  → Constructor is REQUIRED

Rule:
  Has data? → Write constructor
  No data?  → Let compiler handle it
```

---

## ISP vs Fat Interface — Comparison

```
┌──────────────────────┬────────────────┬──────────────────┐
│ Feature              │ Fat Interface  │ ISP              │
├──────────────────────┼────────────────┼──────────────────┤
│ Empty methods?       │ ❌ Yes         │ ✅ None          │
│ Easy to extend?      │ ❌ Hard        │ ✅ Easy          │
│ Recompile all?       │ ❌ Yes         │ ✅ Only affected │
│ Misleading API?      │ ❌ Yes         │ ✅ No            │
│ Flexible?            │ ❌ No          │ ✅ Yes           │
│ Functions focused?   │ ❌ No          │ ✅ Yes           │
└──────────────────────┴────────────────┴──────────────────┘
```

---

## Summary

```
┌──────────────────────────────────────────────────────────┐
│                                                          │
│  ISP = Don't force unnecessary methods on classes        │
│                                                          │
│  1. Split FAT interface into SMALL ones                  │
│     IMachine → IPrinter + IScanner + IFax                │
│                                                          │
│  2. Each class implements ONLY what it needs             │
│     Printer → IPrinter only                              │
│     Scanner → IScanner only                              │
│                                                          │
│  3. Combine when needed                                  │
│     IMachine = IPrinter + IScanner                       │
│                                                          │
│  4. Use interface references (IPrinter& not Printer&)    │
│     Enables polymorphism and flexibility                 │
│                                                          │
│  5. Functions accept smallest interface possible         │
│     printDocument(IPrinter&) not printDocument(IMachine&)│
│                                                          │
└──────────────────────────────────────────────────────────┘
```
````
