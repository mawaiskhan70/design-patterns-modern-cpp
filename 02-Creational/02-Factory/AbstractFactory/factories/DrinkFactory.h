#ifndef DRINK_FACTORY_H
#define DRINK_FACTORY_H

#include <string>
#include <map>
#include <memory>
#include "HotDrinkFactory.h"

class DrinkFactory {
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;

public:
    DrinkFactory();
    std::unique_ptr<HotDrink> make_drink(const std::string& name);
};

#endif // DRINK_FACTORY_H
