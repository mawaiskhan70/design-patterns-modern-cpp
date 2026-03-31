#ifndef FILEPERSISTENCE_H
#define FILEPERSISTENCE_H

#include "IPersistence.h"

class FilePersistence : public IPersistence
{
public:
    void save(const Journal& j, const std::string destination) override;
    Journal load(const std::string& source) override;
};

#endif // FILEPERSISTENCE_H
