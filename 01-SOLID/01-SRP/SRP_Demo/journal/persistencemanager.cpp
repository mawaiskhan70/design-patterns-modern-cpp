#include "persistencemanager.h"
#include <fstream>
#include <iostream>
PersistenceManager::PersistenceManager() {}

void PersistenceManager::save(const Journal &j, const std::string &filename)
{
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cerr << "Error: Cannot open " << filename << std::endl;
        return;
    }

    ofs << j.m_title << std::endl;
    ofs << "---" << std::endl;
    for (const auto& entry : j.m_entries) {
        ofs << entry << std::endl;
    }
    std::cout << "Saved to: " << filename << std::endl;
}

Journal PersistenceManager::load(const std::string &filename)
{
    std::ifstream ifs(filename);
    if (!ifs) {
        std::cerr << "Error: Cannot open " << filename << std::endl;
        return Journal("Empty");
    }

    std::string title;
    std::getline(ifs, title);

    Journal j(title);
    std::string line;
    std::getline(ifs, line);

    while (std::getline(ifs, line)) {
        j.m_entries.push_back(line);
    }
    std::cout << "Loaded from: " << filename << std::endl;
    return j;
}
