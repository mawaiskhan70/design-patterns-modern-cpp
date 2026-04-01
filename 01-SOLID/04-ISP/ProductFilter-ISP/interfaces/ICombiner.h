#ifndef ICOMBINER_H
#define ICOMBINER_H

#include "ISpecification.h"

// ═══════════════════════════════════════════
// ISP: ONLY combines two specifications
// Does NOT check items
// Does NOT filter items
// ═══════════════════════════════════════════

// Operator && to combine any two specifications
template <typename T>
AndSpecification<T> operator&&(const ISpecification<T>& first,
                               const ISpecification<T>& second) {
    return { first, second };
}

#endif // ICOMBINER_H
