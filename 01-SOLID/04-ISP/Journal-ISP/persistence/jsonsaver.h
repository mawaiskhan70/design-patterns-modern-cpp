#ifndef JSON_SAVER_H
#define JSON_SAVER_H

#include "ISaver.h"

class JsonSaver : public ISaver {
public:
    void save(const Journal& journal, const std::string destination) override;
};

#endif // JSON_SAVER_H
