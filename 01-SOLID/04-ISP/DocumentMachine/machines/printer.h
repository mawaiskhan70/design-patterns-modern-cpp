#ifndef PRINTER_H
#define PRINTER_H

#include "IPrinter.h"

class Printer : public IPrinter
{
public:
    void print(Document& doc) override;

};

#endif // PRINTER_H
