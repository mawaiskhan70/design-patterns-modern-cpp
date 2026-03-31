#ifndef ISCANNER_H
#define ISCANNER_H

#include "document.h"

class IScanner {

public:
    virtual ~IScanner() = default;
    virtual void scan(Document& doc) = 0 ;
};
#endif // ISCANNER_H
