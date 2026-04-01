#include "jsonsaver.h"
#include <fstream>
#include <iostream>

void JsonSaver::save(const Journal &journal, const string destination)
{
    std::ofstream ofs(destination);
    ofs << "{" << std::endl;
    ofs << "  \"title\": \"" << journal.m_title << "\"," << std::endl;
    ofs << "  \"entries\": [" << std::endl;
    for (size_t i = 0; i < journal.m_entries.size(); i++) {
        ofs << "    \"" << journal.m_entries[i] << "\"";
        if (i < journal.m_entries.size() - 1) ofs << ",";
        ofs << std::endl;
    }
    ofs << "  ]" << std::endl;
    ofs << "}" << std::endl;
    std::cout << "[JsonSaver] Saved to: " << destination << std::endl;
}
