#ifndef COLORSPECIFICATION_H
#define COLORSPECIFICATION_H

#include "product.h"
#include "specification.h"

class ColorSpecification : public Specification<Product>
{
public:
    Color color;

    explicit ColorSpecification(Color color);
    bool is_satisfied(Product *item) const override;

};

#endif // COLORSPECIFICATION_H
