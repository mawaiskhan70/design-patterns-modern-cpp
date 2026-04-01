#include "filepersistence.h"
#include <fstream>
#include <iostream>

void FilePersistence::save(const Journal &j, const string &destination)
{
    std::ofstream ofs(destination);
    if (!ofs) {
        std::cerr << "[FILE] Error: Cannot open " << destination << std::endl;
        return;
    }

    ofs << j.title << std::endl;
    ofs << "---" << std::endl;
    for (const auto& entry : j.entries) {
        ofs << entry << std::endl;
    }

    std::cout << "[FILE] Saved to: " << destination << std::endl;
}

Journal FilePersistence::load(const string &source)
{
    std::ifstream ifs(source);
    if (!ifs) {
        std::cerr << "[FILE] Error: Cannot open " << source << std::endl;
        return Journal("Empty");
    }

    std::string title;
    std::getline(ifs, title);

    Journal j(title);
    std::string line;
    std::getline(ifs, line);  // skip "---"

    while (std::getline(ifs, line)) {
        j.entries.push_back(line);
    }

    std::cout << "[FILE] Loaded from: " << source << std::endl;
    return j;
}
