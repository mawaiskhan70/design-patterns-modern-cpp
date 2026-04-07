#ifndef COFFEE_H
#define COFFEE_H

#include "HotDrink.h"

class Coffee : public HotDrink {
public:
    void prepare(int volume) override;
};

#endif // COFFEE_H
