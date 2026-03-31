#include "scanner.h"
#include <iostream>

void Scanner::scan(Document &doc)
{
    std::cout <<"[Scanner] Scanning: "<< doc.m_name<< std::endl;
    std::cout <<" Content: "<< doc.m_content<< std::endl;
}
