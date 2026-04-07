#ifndef TEA_FACTORY_H
#define TEA_FACTORY_H

#include "HotDrinkFactory.h"
#include "Tea.h"

class TeaFactory : public HotDrinkFactory {
public:
    std::unique_ptr<HotDrink> make() const override {
        return std::make_unique<Tea>();
    }
};

#endif // TEA_FACTORY_H
