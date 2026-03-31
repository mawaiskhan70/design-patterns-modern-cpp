#include <iostream>
#include <vector>
#include <memory>

#include "journal.h"
#include "ISaver.h"
#include "ILoader.h"
#include "filesaver.h"
#include "fileloader.h"
#include "jsonsaver.h"
#include "filepersistence.h"

using namespace std;

// Takes ONLY ISaver — doesn't care about loading
void saveJournal(ISaver& saver, const Journal& j, const string& dest) {
    saver.save(j, dest);
}

// Takes ONLY ILoader — doesn't care about saving
Journal loadJournal(ILoader& loader, const string& source) {
    return loader.load(source);
}

int main() {

    // ── Create Journal ──
    Journal journal("Dear Diary");
    journal.add("I learned ISP today");
    journal.add("Small interfaces are better");
    journal.add("Don't force unnecessary methods");

    cout << "Journal: " << journal.m_title << endl;
    for (const auto& entry : journal.m_entries) {
        cout << "  " << entry << endl;
    }

    // ── ISP: Use ONLY what you need! ──

    // Only need to SAVE? Use ISaver!
    cout << "\n=== Save Only ===" << endl;
    FileSaver fileSaver;
    JsonSaver jsonSaver;

    saveJournal(fileSaver, journal, "diary.txt");
    saveJournal(jsonSaver, journal, "diary.json");

    // Only need to LOAD? Use ILoader!
    cout << "\n=== Load Only ===" << endl;
    FileLoader fileLoader;
    Journal loaded = loadJournal(fileLoader, "diary.txt");
    cout << "Loaded: " << loaded.m_title << endl;
    for (const auto& entry : loaded.m_entries) {
        cout << "  " << entry << endl;
    }

    // Need BOTH? Use IPersistence!
    cout << "\n=== Full Persistence (Save + Load) ===" << endl;
    FilePersistence fp;
    saveJournal(fp, journal, "diary_full.txt");       // Works as saver!
    Journal loaded2 = loadJournal(fp, "diary_full.txt"); // Works as loader!
    cout << "Loaded: " << loaded2.m_title << endl;

    // ── ISP Power: Different savers in vector ──
    cout << "\n=== Multiple Savers ===" << endl;
    vector<unique_ptr<ISaver>> savers;
    savers.push_back(make_unique<FileSaver>());
    savers.push_back(make_unique<JsonSaver>());

    for (auto& saver : savers) {
        saver->save(journal, "diary_multi");
    }

    return 0;
}
