#ifndef PERSISTENCEMANAGER_H
#define PERSISTENCEMANAGER_H
#include <string>
#include "journal.h"
class PersistenceManager
{
public:
    PersistenceManager();
public:
    static void save(const Journal& j, const std::string& filename);
    static Journal load(const std::string& filename);
};

#endif // PERSISTENCEMANAGER_H
