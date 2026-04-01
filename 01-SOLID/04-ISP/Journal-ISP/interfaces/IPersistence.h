#ifndef IPERSISTENCE_H
#define IPERSISTENCE_H

#include "ISaver.h"
#include "ILoader.h"

class IPersistence : public ISaver, public ILoader
{
public:
    virtual ~IPersistence() = default;
};
#endif // IPERSISTENCE_H
