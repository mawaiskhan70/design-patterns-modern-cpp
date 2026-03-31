#include "filepersistence.h"
#include <fstream>
#include <iostream>

void FilePersistence::save(const Journal &j, const string destination)
{
    std::ofstream ofs(destination);
    ofs << j.m_title << std::endl;
    ofs << "---" << std::endl;
    for (const auto& entry : j.m_entries) {
        ofs << entry << std::endl;
    }
    std::cout << "[FilePersistence] Saved to: " << destination << std::endl;
}

Journal FilePersistence::load(const string &source)
{
    std::ifstream ifs(source);
    std::string title;
    std::getline(ifs, title);

    Journal j(title);
    std::string line;
    std::getline(ifs, line);

    while (std::getline(ifs, line)) {
        j.m_entries.push_back(line);
    }
    std::cout << "[FilePersistence] Loaded from: " << source << std::endl;
    return j;
}
