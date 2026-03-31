#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

enum class Color { red, green, blue };
enum class Size { small, medium, large };

class Product {
public:
    std::string name;
    Color color;
    Size size;

    Product(const std::string& name, Color color, Size size);
};

#endif // PRODUCT_H
