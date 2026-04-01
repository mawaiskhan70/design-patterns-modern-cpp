#include "machine.h"

Machine::Machine(IPrinter &printer, IScanner &scanner) : m_printer(printer), m_scanner(scanner)
//                       ^^^^^^^^^           ^^^^^^^^^
//                       Accepts ANY class   Accepts ANY class
//                        that inherits       that inherits
//                          IPrinter            IScanner
{

}

void Machine::print(Document &doc)
{
    m_printer.print(doc);
}

void Machine::scan(Document &doc)
{
    m_scanner.scan(doc);
}


