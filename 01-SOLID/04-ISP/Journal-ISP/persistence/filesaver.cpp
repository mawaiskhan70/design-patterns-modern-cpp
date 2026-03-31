#include "filesaver.h"
#include <fstream>
#include <iostream>

void FileSaver::save(const Journal &journal, const string destination)
{
    std::ofstream ofs(destination);
    ofs << journal.m_title << std::endl;
    ofs << "---" << std::endl;
    for (const auto& entry : journal.m_entries) {
        ofs << entry << std::endl;
    }
    std::cout << "[FileSaver] Saved to: " << destination << std::endl;
}
