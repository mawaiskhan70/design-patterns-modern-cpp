#ifndef IPERSISTENCE_H
#define IPERSISTENCE_H

#include <string>
#include "journal.h"

class IPersistence
{
public:
    virtual ~IPersistence() = default;
    virtual void save (const Journal& j, const std::string& destination)= 0;
    virtual Journal load(const std::string& source) = 0;
};

#endif // IPERSISTENCE_H
