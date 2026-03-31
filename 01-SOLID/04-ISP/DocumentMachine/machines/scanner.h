#ifndef SCANNER_H
#define SCANNER_H

#include "IScanner.h"

class Scanner : public IScanner
{
public:
    void scan(Document& doc) override;
};

#endif // SCANNER_H
