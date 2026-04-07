#include <iostream>
#include "Point.h"

using namespace std;

int main() {

    cout << "=== Inner Factory Pattern ===" << endl;

    // ❌ Can't create Point directly
    // Point p(1, 2);  // ERROR!

    // ❌ Can't create factory instance (why bother? it's static methods)
    // Point::PointFactory pf;  // Can but useless

    // ✅ Use through Point::Factory
    auto p1 = Point::Factory.NewCartesian(10.0f, 20.0f);
    cout << "Cartesian: (" << p1.getX() << ", " << p1.getY() << ")" << endl;

    auto p2 = Point::Factory.NewPolar(5.0f, 1.571f); // 90 degrees
    cout << "Polar: (" << p2.getX() << ", " << p2.getY() << ")" << endl;

    // ✅ Alternative: Use class name directly
    auto p3 = Point::PointFactory::NewCartesian(15.0f, 25.0f);
    cout << "Direct: (" << p3.getX() << ", " << p3.getY() << ")" << endl;

    return 0;
}
