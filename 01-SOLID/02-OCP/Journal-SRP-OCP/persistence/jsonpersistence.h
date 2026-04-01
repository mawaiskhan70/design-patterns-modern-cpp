#ifndef JSONPERSISTENCE_H
#define JSONPERSISTENCE_H

#include "ipersistence.h"

class JsonPersistence : public IPersistence
{
public:
    void save(const Journal& J, const string& destination) override;
    Journal load(const string &source) override;
};

#endif // JSONPERSISTENCE_H
