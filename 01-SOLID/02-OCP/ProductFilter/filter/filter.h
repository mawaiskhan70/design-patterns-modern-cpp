#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include "specification.h"

// ═══════════════════════════════════════════════════════
// Base Filter Interface
// CLOSED for modification — this NEVER changes!
// OPEN for extension — anyone can create new filters!
// ═══════════════════════════════════════════════════════

template <typename T>
class Filter {
public:
    virtual ~Filter() = default;
    virtual std::vector<T*> filter(
        std::vector<T*> items,
        Specification<T>& spec) = 0;
};

#endif // FILTER_H
