#ifndef FILEPERSISTENCE_H
#define FILEPERSISTENCE_H

#include<ipersistence.h>

class FilePersistence : public IPersistence
{
public:
    void save(const Journal& j, const string& destination) override;
    Journal load(const string& source)override;
};

#endif // FILEPERSISTENCE_H
