#ifndef FILESAVER_H
#define FILESAVER_H

#include "ISaver.h"

class FileSaver : public ISaver
{
public:
    void save(const Journal& journal, const std::string destination) override;
};

#endif // FILESAVER_H
