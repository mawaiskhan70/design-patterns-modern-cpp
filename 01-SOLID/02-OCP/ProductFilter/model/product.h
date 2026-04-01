#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
enum class Color {red, green, blue};
enum class Size {small, medium, large};
using namespace std;
class Product
{
public:
    string name;
    Color color;
    Size size;
    Product(const string& name, Color color, Size size);
};

#endif // PRODUCT_H
