#ifndef ISPECIFICATION_H
#define ISPECIFICATION_H

// Forward declaration
template <typename T> class AndSpecification;

// ═══════════════════════════════════════════
// ISP: ONLY checks if item matches criteria
// Does NOT filter, does NOT combine
// ═══════════════════════════════════════════

template <typename T>
class ISpecification {
public:
    virtual ~ISpecification() = default;
    virtual bool is_satisfied(T* item) const = 0;
};

#endif // ISPECIFICATION_H
