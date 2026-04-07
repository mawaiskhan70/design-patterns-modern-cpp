#include <iostream>
#include <memory>
#include "HotDrink.h"
#include "Tea.h"
#include "Coffee.h"
#include "DrinkFactory.h"

using namespace std;

// ❌ Bad way — manual if-else
unique_ptr<HotDrink> make_drink_manual(string type) {
    unique_ptr<HotDrink> drink;
    if (type == "tea") {
        drink = make_unique<Tea>();
        drink->prepare(200);
    } else {
        drink = make_unique<Coffee>();
        drink->prepare(50);
    }
    return drink;
}

int main() {

    cout << "=== Manual Way (Without Factory) ===" << endl;
    auto manual_tea = make_drink_manual("tea");

    cout << "\n=== Abstract Factory Pattern ===" << endl;
    DrinkFactory df;

    auto tea = df.make_drink("tea");
    auto coffee = df.make_drink("coffee");

    return 0;
}
