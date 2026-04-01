#ifndef JOURNAL_H
#define JOURNAL_H

#include <string>
#include <vector>
using namespace std;
class Journal
{
public:
    string title;
    vector<string> entries;
    explicit Journal(const string& title);

    void add(const string& entry);
    void remove(int index);
    int count()const;

    // ❌ NO save() here — SRP!
    // ❌ NO load() here — SRP!
    // Journal ONLY manages entries!
};

#endif // JOURNAL_H
