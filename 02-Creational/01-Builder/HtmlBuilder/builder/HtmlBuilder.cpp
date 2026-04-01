#include "HtmlBuilder.h"
#include <sstream>

namespace html {

HtmlBuilder::HtmlBuilder(const std::string& rootName)
    : root(rootName) {}

HtmlBuilder& HtmlBuilder::addChild(const std::string& childName,
                                     const std::string& childText) {
    // Create a child tag wrapper
    class ChildTag : public Tag {
    public:
        ChildTag(const std::string& name, const std::string& text)
            : Tag(name, text) {}
    };

    root.children.emplace_back(ChildTag(childName, childText));
    return *this;  // Return self for chaining!
}

HtmlBuilder& HtmlBuilder::addChild(const Tag& child) {
    root.children.emplace_back(child);
    return *this;  // Return self for chaining!
}

std::string HtmlBuilder::str() const {
    std::ostringstream oss;
    oss << root;
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const HtmlBuilder& builder) {
    os << builder.root;
    return os;
}

Tag HtmlBuilder::build() const {
    return root;
}

} // namespace html
