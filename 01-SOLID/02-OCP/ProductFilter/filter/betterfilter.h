#ifndef BETTERFILTER_H
#define BETTERFILTER_H
#include "filter.h"
#include "product.h"

class BetterFilter : public Filter <Product>
{
public:
    std::vector<Product*> filter(
        std::vector<Product*> items,
        Specification<Product>& spec) override;
};

#endif // BETTERFILTER_H
