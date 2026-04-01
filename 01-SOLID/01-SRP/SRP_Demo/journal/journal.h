#ifndef JOURNAL_H
#define JOURNAL_H

#include <string>
#include <vector>

class Journal
{
public:
    std::string m_title;
    std::vector<std::string> m_entries;
    explicit Journal(const std::string& title);
    void add(const std::string& entry);
    int count() const;
};

#endif // JOURNAL_H
