# Journal — SRP + OCP Combined

## Principles Applied

### SRP (Single Responsibility)
```
Journal class → ONLY manages entries (add, remove, count)
               → Does NOT know about saving/loading
               → Has ONE reason to change

FilePersistence  → ONLY handles file save/load
JsonPersistence  → ONLY handles JSON save/load
Each class       → ONE job, ONE reason to change
```

### OCP (Open/Closed)
```
IPersistence interface → CLOSED (never changes)
FilePersistence        → OPEN (extends interface)
JsonPersistence        → OPEN (extends interface)

Adding XML support?
  → Create XmlPersistence.h/.cpp (NEW file)
  → Implement IPersistence interface
  → NOTHING existing changes!
```

## How To Add New Format (e.g., XML)

1. Create `persistence/XmlPersistence.h`
2. Create `persistence/XmlPersistence.cpp`
3. Implement `IPersistence` interface
4. Use in main.cpp

```cpp
// Step 1-2: New files
class XmlPersistence : public IPersistence {
    void save(const Journal& j, const string& dest) override;
    Journal load(const string& source) override;
};

// Step 3: Use — just ONE line!
savers.push_back(make_unique<XmlPersistence>());
```

**Zero existing files modified!** ✅

## Files Changed vs Unchanged
```
UNCHANGED (CLOSED):
  ✅ journal.h / journal.cpp
  ✅ IPersistence.h
  ✅ FilePersistence.h / .cpp
  ✅ JsonPersistence.h / .cpp
  ✅ saveJournal() function

ADDED (OPEN):
  🆕 XmlPersistence.h / .cpp
  📝 main.cpp (one new line)
```
