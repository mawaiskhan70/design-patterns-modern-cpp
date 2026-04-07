#ifndef HOT_DRINK_H
#define HOT_DRINK_H

#include <iostream>

class HotDrink {
public:
    virtual ~HotDrink() = default;
    virtual void prepare(int volume) = 0;
};

#endif // HOT_DRINK_H
