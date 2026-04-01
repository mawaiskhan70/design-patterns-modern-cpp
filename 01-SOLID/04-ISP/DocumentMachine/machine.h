#ifndef MACHINE_H
#define MACHINE_H

#include "IMachine.h"

class Machine : public IMachine
{
public:
    IPrinter& m_printer;
    IScanner& m_scanner;
    explicit Machine(IPrinter& printer,  IScanner& scanner);
    void print(Document& doc) override;
    void scan(Document& doc) override;

};

#endif // MACHINE_H
