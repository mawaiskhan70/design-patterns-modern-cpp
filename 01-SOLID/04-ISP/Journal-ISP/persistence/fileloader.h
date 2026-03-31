#ifndef FILELOADER_H
#define FILELOADER_H
#include "ILoader.h"

class FileLoader : public ILoader
{
public:

    Journal load (const std::string& source) override;
};

#endif // FILELOADER_H
