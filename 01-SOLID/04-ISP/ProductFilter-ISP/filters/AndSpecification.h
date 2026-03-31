#ifndef AND_SPECIFICATION_H
#define AND_SPECIFICATION_H

#include "ISpecification.h"

// Combines TWO specifications into one
// Template class — all code in header!
template <typename T>
class AndSpecification : public ISpecification<T> {
public:
    const ISpecification<T>& first;
    const ISpecification<T>& second;

    AndSpecification(const ISpecification<T>& first,
                     const ISpecification<T>& second)
        : first(first), second(second) {}

    bool is_satisfied(T* item) const override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

#endif // AND_SPECIFICATION_H
