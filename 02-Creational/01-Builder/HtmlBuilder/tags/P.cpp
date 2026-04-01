#include "P.h"

namespace html {

P::P(const std::string& text)
    : Tag("p", text) {}

P::P(std::initializer_list<Tag> children)
    : Tag("p", children) {}

} // namespace html
