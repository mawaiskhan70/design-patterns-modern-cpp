#include "journal.h"
#include <boost/lexical_cast.hpp>

Journal::Journal(const string &title) : title(title)
{

}

void Journal::add(const string &entry)
{

    static int count = 1;
    entries.push_back(boost::lexical_cast<string>(count ++) + " : " + entry);
}

void Journal::remove(int index)
{
    if (index >=0 && index <static_cast<int>(entries.size()))
    {
        entries.erase(entries.begin() + index);
    }
}

int Journal::count() const
{
    return entries.size();
}
