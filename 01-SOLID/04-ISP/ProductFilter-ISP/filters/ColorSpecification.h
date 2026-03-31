#ifndef COLOR_SPECIFICATION_H
#define COLOR_SPECIFICATION_H

#include "ISpecification.h"
#include "product.h"

// ONLY checks color — nothing else!
class ColorSpecification : public ISpecification<Product> {
public:
    Color color;

    explicit ColorSpecification(Color color);
    bool is_satisfied(Product* item) const override;
};

#endif // COLOR_SPECIFICATION_H
