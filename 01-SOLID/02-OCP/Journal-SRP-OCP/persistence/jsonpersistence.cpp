#include "jsonpersistence.h"
#include <fstream>
#include <iostream>

void JsonPersistence::save(const Journal& j,
                           const std::string& destination) {
    std::ofstream ofs(destination);
    if (!ofs) {
        std::cerr << "[JSON] Error: Cannot open " << destination << std::endl;
        return;
    }

    ofs << "{" << std::endl;
    ofs << "  \"title\": \"" << j.title << "\"," << std::endl;
    ofs << "  \"entries\": [" << std::endl;

    for (size_t i = 0; i < j.entries.size(); i++) {
        ofs << "    \"" << j.entries[i] << "\"";
        if (i < j.entries.size() - 1) ofs << ",";
        ofs << std::endl;
    }

    ofs << "  ]" << std::endl;
    ofs << "}" << std::endl;

    std::cout << "[JSON] Saved to: " << destination << std::endl;
}

Journal JsonPersistence::load(const std::string& source) {
    // Simplified — real code would parse JSON
    std::cout << "[JSON] Loading from: " << source << std::endl;
    return Journal("From JSON");
}
