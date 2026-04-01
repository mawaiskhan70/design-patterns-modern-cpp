#ifndef BETTER_FILTER_H
#define BETTER_FILTER_H

#include <vector>
#include "IFilter.h"
#include "product.h"

// ONLY filters — doesn't define specifications!
class BetterFilter : public IFilter<Product> {
public:
    std::vector<Product*> filter(
        std::vector<Product*> items,
        ISpecification<Product>& spec) override;
};

#endif // BETTER_FILTER_H
