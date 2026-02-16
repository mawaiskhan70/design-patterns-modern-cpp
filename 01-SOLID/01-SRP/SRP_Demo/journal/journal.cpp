#include "journal.h"
#include <boost/lexical_cast.hpp>
Journal::Journal(const std::string &title) : m_title(title)
{
}

void Journal::add(const std::string& entry)
{
    static int count =1;
    m_entries.push_back(
        boost::lexical_cast<std::string>(count++) + ": " + entry
        );

}

int Journal::count() const
{
    return m_entries.size();
}
