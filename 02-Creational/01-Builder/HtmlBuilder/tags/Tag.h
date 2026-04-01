#ifndef TAG_H
#define TAG_H

#include <string>
#include <vector>
#include <iostream>
#include <utility>

namespace html {

class Tag{

public:
    std::string name;
    std::string text;
    std::vector<Tag> children;
    std::vector<std::pair<std::string,std::string>> attributes;

    // Print tag to output stream
    friend std::ostream& operator<<(std::ostream& os, const Tag& tag);

    // Get HTML as string
    std::string str() const;

protected:
    // Protected — only child classes can create Tags!
    Tag(const std::string& name, const std::string& text);
    Tag(const std::string& name, const std::vector<Tag>& children);

};

}
#endif // TAG_H
