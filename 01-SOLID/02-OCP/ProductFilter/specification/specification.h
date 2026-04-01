#ifndef SPECIFICATION_H
#define SPECIFICATION_H

// Forward declaration
template <typename T> class AndSpecification;
// ═══════════════════════════════════════════════════════
// Base Specification Interface
// CLOSED for modification — this NEVER changes!
// OPEN for extension — anyone can create new specs!
// ═══════════════════════════════════════════════════════

template <typename T>
class Specification
{
public:
    virtual ~Specification() = default;
    virtual bool is_satisfied(T* item) const = 0;
};

// ═══════════════════════════════════════════════════════
// Operator && overload — combine two specifications
// ═══════════════════════════════════════════════════════

template <typename T>
AndSpecification<T> operator&&(const Specification<T>& first,
                               const Specification<T>& second) {
    return { first, second };
}
#endif // SPECIFICATION_H
