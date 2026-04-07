#include "DrinkFactory.h"
#include "TeaFactory.h"
#include "CoffeeFactory.h"

DrinkFactory::DrinkFactory() {
    hot_factories["tea"] = std::make_unique<TeaFactory>();
    hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
}

std::unique_ptr<HotDrink> DrinkFactory::make_drink(const std::string& name) {
    auto drink = hot_factories[name]->make();
    drink->prepare(200);
    return drink;
}
