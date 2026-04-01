#ifndef IMG_H
#define IMG_H

#include "Tag.h"

namespace html {

// Image tag <img src="url"/>
class IMG : public Tag {
public:
    explicit IMG(const std::string& url);
};

} // namespace html

#endif // IMG_H
