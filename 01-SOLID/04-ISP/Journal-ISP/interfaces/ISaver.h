#ifndef ISAVER_H
#define ISAVER_H
#include <string>
#include "journal.h"

class ISaver {
public:
    virtual ~ISaver() = default;
    virtual void save(const Journal & journal, const std::string destination) = 0;

};
#endif // ISAVER_H
