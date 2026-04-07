#ifndef TEA_H
#define TEA_H

#include "HotDrink.h"

class Tea : public HotDrink {
public:
    void prepare(int volume) override;
};

#endif // TEA_H
