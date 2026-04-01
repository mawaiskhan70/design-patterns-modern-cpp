#include "printer.h"
#include <iostream>

void Printer::print(Document &doc)
{
    std::cout <<"[Printer] Printing: "<< doc.m_name<< std::endl;
    std::cout <<" Content: "<< doc.m_content<< std::endl;
}
