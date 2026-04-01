#ifndef IPRINTER_H
#define IPRINTER_H
#include "document.h"

class IPrinter {

public:
    virtual ~IPrinter() = default;
    virtual void print(Document& doc) =0;

};

#endif // IPRINTER_H
