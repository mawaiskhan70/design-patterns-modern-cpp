#ifndef SIZE_SPECIFICATION_H
#define SIZE_SPECIFICATION_H

#include "ISpecification.h"
#include "product.h"

// ONLY checks size — nothing else!
class SizeSpecification : public ISpecification<Product> {
public:
    Size size;

    explicit SizeSpecification(Size size);
    bool is_satisfied(Product* item) const override;
};

#endif // SIZE_SPECIFICATION_H
