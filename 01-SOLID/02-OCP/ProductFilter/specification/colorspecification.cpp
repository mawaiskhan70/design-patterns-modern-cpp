#include "colorspecification.h"

ColorSpecification::ColorSpecification(Color color) : color(color)
{

}

bool ColorSpecification::is_satisfied(Product *item) const
{
    return item->color ==  color;
}
