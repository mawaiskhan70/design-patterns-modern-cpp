#ifndef HTML_BUILDER_H
#define HTML_BUILDER_H

#include <string>
#include "Tag.h"

namespace html {

// Builder pattern — constructs HTML step by step
class HtmlBuilder {
public:
    // Start building with a root tag
    explicit HtmlBuilder(const std::string& rootName);

    // Add child with text
    HtmlBuilder& addChild(const std::string& childName,
                          const std::string& childText);

    // Add child Tag directly
    HtmlBuilder& addChild(const Tag& child);

    // Get result as string
    std::string str() const;

    // Print
    friend std::ostream& operator<<(std::ostream& os,
                                    const HtmlBuilder& builder);

    // Get the built tag
    Tag build() const;

private:
    // HtmlBuilder needs access to Tag constructor
    // So we use a simple wrapper
    class RootTag : public Tag {
    public:
        RootTag(const std::string& name) : Tag(name, "") {}
    };

    RootTag root;
};

} // namespace html

#endif // HTML_BUILDER_H
