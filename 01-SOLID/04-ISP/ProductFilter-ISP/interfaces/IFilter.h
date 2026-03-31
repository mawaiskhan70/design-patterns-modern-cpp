#ifndef IFILTER_H
#define IFILTER_H

#include <vector>
#include "ISpecification.h"

// ═══════════════════════════════════════════
// ISP: ONLY filters items using a specification
// Does NOT define specifications
// Does NOT combine specifications
// ═══════════════════════════════════════════

template <typename T>
class IFilter {
public:
    virtual ~IFilter() = default;
    virtual std::vector<T*> filter(
        std::vector<T*> items,
        ISpecification<T>& spec) = 0;
};

#endif // IFILTER_H
