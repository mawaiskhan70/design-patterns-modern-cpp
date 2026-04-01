#ifndef P_H
#define P_H

#include "Tag.h"
#include <initializer_list>

namespace html {

class P: public Tag {

    public:
    // Text paragraph: <p>some text</p>
    explicit P(const std::string& text);

    // Paragraph with children: <p><img/>...</p>
    P(std::initializer_list<Tag> children);

};

}
#endif
