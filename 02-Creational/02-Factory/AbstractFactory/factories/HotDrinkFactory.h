#ifndef HOT_DRINK_FACTORY_H
#define HOT_DRINK_FACTORY_H

#include <memory>
#include "HotDrink.h"

class HotDrinkFactory {
public:
    virtual ~HotDrinkFactory() = default;
    virtual std::unique_ptr<HotDrink> make() const = 0;
};

#endif // HOT_DRINK_FACTORY_H
