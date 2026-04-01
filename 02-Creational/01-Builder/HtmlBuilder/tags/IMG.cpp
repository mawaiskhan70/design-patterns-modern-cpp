#include "IMG.h"

namespace html {

IMG::IMG(const std::string& url)
    : Tag("img", "") {
    attributes.emplace_back(std::make_pair("src", url));
}

} // namespace html
