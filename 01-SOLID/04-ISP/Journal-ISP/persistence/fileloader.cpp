#include "fileloader.h"
#include <fstream>
#include <iostream>

Journal FileLoader::load(const string &source)
{
    std::ifstream ifs(source);
    std::string title;
    std::getline(ifs, title);

    Journal j(title);
    std::string line;
    std::getline(ifs, line);  // skip "---"

    while (std::getline(ifs, line)) {
        j.m_entries.push_back(line);
    }
    std::cout << "[FileLoader] Loaded from: " << source << std::endl;
    return j;
}
