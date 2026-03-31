#include "SizeSpecification.h"

SizeSpecification::SizeSpecification(Size size)
    : size(size) {}

bool SizeSpecification::is_satisfied(Product* item) const {
    return item->size == size;
}
