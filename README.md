# Design-Patterns-in-Modern-C-
Design Patterns in Modern C++ — Notes, implementations, and examples  from Dmitri Nesteruk's Udemy course. Covers SOLID principles,  creational, structural, and behavioral patterns with real-world code.
# 🎯 Design Patterns in Modern C++


[![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Udemy](https://img.shields.io/badge/Udemy-Course-purple.svg)](https://www.udemy.com/course/patterns-cplusplus/)
[![Status](https://img.shields.io/badge/Status-In%20Progress-yellow.svg)]()

Personal implementations, notes, and examples from the Udemy course
**"Design Patterns in Modern C++"** by **Dmitri Nesteruk**.

Each pattern is implemented with clean, well-documented code following
modern C++ standards (C++17) with real-world examples.

---

## 📚 Course Content

### 🏗️ SOLID Design Principles

| # | Principle | Status | Description |
|---|-----------|--------|-------------|
| 1 | [Single Responsibility (SRP)](./01-SOLID/01-SRP/) | ✅ Done | Each class should have only one reason to change  |
| 2 | [Open/Closed (OCP)](./01-SOLID/02-OCP/) | ✅ Done | Open for extension, closed for modification |
| 3 | [Liskov Substitution (LSP)](./01-SOLID/03-LSP/) | 🔄 In Progress | Subtypes must be substitutable for base types |
| 4 | [Interface Segregation (ISP)](./01-SOLID/04-ISP/) | ⬚ Pending | Many specific interfaces over one general |
| 5 | [Dependency Inversion (DIP)](./01-SOLID/05-DIP/) | ⬚ Pending | Depend on abstractions, not concretions |

### 🔨 Creational Patterns

| # | Pattern | Status | Description |
|---|---------|--------|-------------|
| 1 | [Builder](./02-Creational/01-Builder/) | ⬚ Pending | Construct complex objects step by step |
| 2 | [Factory](./02-Creational/02-Factory/) | ⬚ Pending | Create objects without specifying exact class |
| 3 | [Prototype](./02-Creational/03-Prototype/) | ⬚ Pending | Clone existing objects |
| 4 | [Singleton](./02-Creational/04-Singleton/) | ⬚ Pending | Ensure single instance of a class |

### 🧱 Structural Patterns

| # | Pattern | Status | Description |
|---|---------|--------|-------------|
| 1 | [Adapter](./03-Structural/01-Adapter/) | ⬚ Pending | Make incompatible interfaces work together |
| 2 | [Bridge](./03-Structural/02-Bridge/) | ⬚ Pending | Separate abstraction from implementation |
| 3 | [Composite](./03-Structural/03-Composite/) | ⬚ Pending | Compose objects into tree structures |
| 4 | [Decorator](./03-Structural/04-Decorator/) | ⬚ Pending | Add behavior to objects dynamically |
| 5 | [Facade](./03-Structural/05-Facade/) | ⬚ Pending | Simplified interface to complex subsystem |
| 6 | [Flyweight](./03-Structural/06-Flyweight/) | ⬚ Pending | Share common state between objects |
| 7 | [Proxy](./03-Structural/07-Proxy/) | ⬚ Pending | Placeholder for another object |

### 🔄 Behavioral Patterns

| # | Pattern | Status | Description |
|---|---------|--------|-------------|
| 1 | [Chain of Responsibility](./04-Behavioral/01-ChainOfResponsibility/) | ⬚ Pending | Pass request along a chain of handlers |
| 2 | [Command](./04-Behavioral/02-Command/) | ⬚ Pending | Encapsulate request as an object |
| 3 | [Interpreter](./04-Behavioral/03-Interpreter/) | ⬚ Pending | Define grammar and interpret sentences |
| 4 | [Iterator](./04-Behavioral/04-Iterator/) | ⬚ Pending | Access elements sequentially |
| 5 | [Mediator](./04-Behavioral/05-Mediator/) | ⬚ Pending | Reduce chaotic dependencies between objects |
| 6 | [Memento](./04-Behavioral/06-Memento/) | ⬚ Pending | Capture and restore object state |
| 7 | [Observer](./04-Behavioral/07-Observer/) | ⬚ Pending | Notify dependents of state changes |
| 8 | [State](./04-Behavioral/08-State/) | ⬚ Pending | Alter behavior when state changes |
| 9 | [Strategy](./04-Behavioral/09-Strategy/) | ⬚ Pending | Define family of interchangeable algorithms |
| 10 | [Template Method](./04-Behavioral/10-TemplateMethod/) | ⬚ Pending | Define skeleton, let subclasses fill in |
| 11 | [Visitor](./04-Behavioral/11-Visitor/) | ⬚ Pending | Add operations without modifying classes |

---

## 📁 Project Structure

```
📁 design-patterns-modern-cpp/
│
├── 📁 01-SOLID/
│   ├── 📁 01-SRP/
│   │   ├── 📁 include/
│   │   │   ├── Journal.h
│   │   │   └── PersistenceManager.h
│   │   ├── 📁 src/
│   │   │   ├── Journal.cpp
│   │   │   ├── PersistenceManager.cpp
│   │   │   └── main.cpp
│   │   ├── CMakeLists.txt
│   │   └── README.md
│   │
│   ├── 📁 02-OCP/
│   │   ├── 📁 include/
│   │   ├── 📁 src/
│   │   ├── CMakeLists.txt
│   │   └── README.md
│   │
│   ├── 📁 03-LSP/
│   ├── 📁 04-ISP/
│   └── 📁 05-DIP/
│
├── 📁 02-Creational/
│   ├── 📁 01-Builder/
│   ├── 📁 02-Factory/
│   ├── 📁 03-Prototype/
│   └── 📁 04-Singleton/
│
├── 📁 03-Structural/
│   ├── 📁 01-Adapter/
│   ├── 📁 02-Bridge/
│   └── ...
│
├── 📁 04-Behavioral/
│   ├── 📁 01-ChainOfResponsibility/
│   ├── 📁 02-Command/
│   └── ...
│
├── 📁 notes/
│   ├── cpp-references.md
│   ├── casting-methods.md
│   └── solid-principles.md
│
├── .gitignore
├── LICENSE
├── README.md
└── CMakeLists.txt
```

---

## 🛠️ Build & Run

### Prerequisites
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10+
- Boost Library (for `lexical_cast`)

### Build Steps

```bash
# Clone the repository
git clone https://github.com/YOUR_USERNAME/design-patterns-modern-cpp.git
cd design-patterns-modern-cpp

# Build a specific pattern (e.g., SRP)
cd 01-SOLID/01-SRP
mkdir build && cd build
cmake ..
make
./srp_demo
```

---

## 📖 Personal Notes

Alongside the code, I maintain revision notes for key C++ concepts
encountered during the course:

| Topic | Notes |
|-------|-------|
| [C++ References (`&`)](./notes/cpp-references.md) | Value, Reference, Const Ref, Pointer — when to use what |
| [Casting Methods](./notes/casting-methods.md) | `static_cast`, `lexical_cast`, `to_string` — comparison |
| [SOLID Principles](./notes/solid-principles.md) | One-pager summary of all 5 principles |

---

## 📝 Key Learnings

- **SRP**: Separate concerns into different classes and files
- **OCP**: Use interfaces/abstract classes to extend without modifying
- **Modern C++**: Leverage `unique_ptr`, `override`, `auto`, range-based loops
- **Real-world structure**: Separate headers (`include/`) and implementations (`src/`)

---

## 🔗 Resources

- 📺 [Udemy Course — Design Patterns in Modern C++](https://www.udemy.com/course/patterns-cplusplus/) by Dmitri Nesteruk
- 📖 [Design Patterns: Elements of Reusable Object-Oriented Software](https://en.wikipedia.org/wiki/Design_Patterns) (Gang of Four)
- 📖 [C++ Reference](https://en.cppreference.com/)
- 📖 [Boost Library Documentation](https://www.boost.org/doc/)

---

## 📄 License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.

---

## ⚠️ Disclaimer

This repository is for **educational purposes**. The code implementations are
my personal interpretations and practice exercises from the course.
All credit for course content goes to **Dmitri Nesteruk**.

---
