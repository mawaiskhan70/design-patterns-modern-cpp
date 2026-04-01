#ifndef SIZESPECIFICATION_H
#define SIZESPECIFICATION_H

#include "product.h"
#include "specification.h"

class SizeSpecification : public Specification <Product>
{
public:
    Size size;
    explicit SizeSpecification(Size size);
    bool is_satisfied(Product *item) const override;
};

#endif // SIZESPECIFICATION_H
