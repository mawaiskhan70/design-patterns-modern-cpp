#ifndef JOURNAL_H
#define JOURNAL_H

#include <string>
#include<vector>

using namespace std;
class Journal
{
public:
    string m_title;
    vector<string> m_entries;
    explicit Journal(const string& title);
    void add (const string& entry);
    int count() const;
};

#endif // JOURNAL_H
