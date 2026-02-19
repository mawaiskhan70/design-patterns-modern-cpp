#include "sizespecification.h"


SizeSpecification::SizeSpecification(Size size)
{

}

bool SizeSpecification::is_satisfied(Product *item) const
{
    return item->size == size;
}
