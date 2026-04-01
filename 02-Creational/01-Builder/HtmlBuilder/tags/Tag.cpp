#include "Tag.h"
#include <sstream>

namespace html {

Tag::Tag(const std::string &name, const std::string &text): name(name), text(text)
{

}

Tag::Tag(const std::string &name, const std::vector<Tag> &children) : name(name), children(children)
{

}

std::ostream& operator<<(std::ostream& os, const Tag& tag) {
    // Opening tag
    os << "<" << tag.name;

    // Attributes
    for (const auto& att : tag.attributes) {
        os << " " << att.first << "=\"" << att.second << "\"";
    }

    // Self-closing or open/close
    if (tag.children.empty() && tag.text.empty()) {
        os << "/>" << std::endl;
    } else {
        os << ">" << std::endl;

        // Text content
        if (!tag.text.empty()) {
            os << tag.text << std::endl;
        }

        // Children (recursive!)
        for (const auto& child : tag.children) {
            os << child;
        }

        // Closing tag
        os << "</" << tag.name << ">" << std::endl;
    }

    return os;
}

std::string Tag::str() const
{
    std::ostringstream oss;
    oss <<  *this;
    return oss.str();

}

}
