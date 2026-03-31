#ifndef ILOADER_H
#define ILOADER_H

#include <string>
#include "journal.h"

class ILoader {
public:
    virtual ~ILoader() = default;
    virtual Journal load (const std::string& source) = 0;
};
#endif // ILOADER_H
