#ifndef ANDSPECIFICATION_H
#define ANDSPECIFICATION_H

#include "specification.h"

// Template class — ALL code MUST be in header!
template <typename T>
class AndSpecification : public Specification<T> {
public:
    const Specification<T>& first;
    const Specification<T>& second;

    AndSpecification(const Specification<T>& first,
                     const Specification<T>& second)
        : first(first), second(second) {}

    bool is_satisfied(T* item) const override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

#endif // ANDSPECIFICATION_H
