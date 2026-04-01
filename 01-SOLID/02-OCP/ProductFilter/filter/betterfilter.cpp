#include "betterfilter.h"

std::vector<Product*> BetterFilter::filter(
    std::vector<Product*> items,
    Specification<Product>& spec) {

    std::vector<Product*> result;
    for (auto& p : items) {
        if (spec.is_satisfied(p)) {
            result.push_back(p);
        }
    }
    return result;
}
