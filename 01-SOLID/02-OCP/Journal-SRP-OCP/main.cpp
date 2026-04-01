#include <iostream>
#include <vector>
#include <memory>

#include "journal.h"
#include "ipersistence.h"
#include "filepersistence.h"
#include "jsonpersistence.h"

using namespace std;

// ═══════════════════════════════════════════════════════
// This function works with ANY persistence type!
// It NEVER changes when new formats are added — OCP! ✅
// ═══════════════════════════════════════════════════════

void saveJournal(IPersistence& persistence,
                 const Journal& j,
                 const string& destination) {
    persistence.save(j, destination);
}

int main() {

    // ── SRP: Journal ONLY manages entries ──
    cout << "=== Creating Journal ===" << endl;
    Journal journal("Dear Diary");
    journal.add("I learned SRP today");
    journal.add("I learned OCP today");
    journal.add("Design patterns are awesome");

    cout << "Journal: " << journal.title << endl;
    cout << "Entries: " << journal.count() << endl;
    for (const auto& entry : journal.entries) {
        cout << "  " << entry << endl;
    }

    // ── OCP: Different persistence methods ──
    // Journal doesn't know or care HOW it's saved!

    // Method 1: Direct usage
    cout << "\n=== Saving (Direct) ===" << endl;
    FilePersistence fileSaver;
    JsonPersistence jsonSaver;

    saveJournal(fileSaver, journal, "diary.txt");
    saveJournal(jsonSaver, journal, "diary.json");

    // Method 2: Polymorphism with vector
    cout << "\n=== Saving (Polymorphism) ===" << endl;
    vector<unique_ptr<IPersistence>> savers;
    savers.push_back(make_unique<FilePersistence>());
    savers.push_back(make_unique<JsonPersistence>());

    for (auto& saver : savers) {
        saver->save(journal, "diary_poly");
    }

    // Method 3: Load back from file
    cout << "\n=== Loading ===" << endl;
    Journal loaded = fileSaver.load("diary.txt");
    cout << "Loaded: " << loaded.title << endl;
    for (const auto& entry : loaded.entries) {
        cout << "  " << entry << endl;
    }

    return 0;
}
