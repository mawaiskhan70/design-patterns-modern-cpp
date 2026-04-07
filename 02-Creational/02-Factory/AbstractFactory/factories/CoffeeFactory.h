#ifndef COFFEE_FACTORY_H
#define COFFEE_FACTORY_H

#include "HotDrinkFactory.h"
#include "Coffee.h"

class CoffeeFactory : public HotDrinkFactory {
public:
    std::unique_ptr<HotDrink> make() const override {
        return std::make_unique<Coffee>();
    }
};

#endif // COFFEE_FACTORY_H
