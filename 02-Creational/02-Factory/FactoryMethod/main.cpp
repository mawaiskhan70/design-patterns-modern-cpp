#include <iostream>
#include "Point.h"
#include "PointFactory.h"

using namespace std;

int main() {

    // ❌ Can't create Point directly — constructor is private!
    // Point p(1, 2);  // ERROR!

    // ✅ Use Factory to create Points
    cout << "=== Factory Method Pattern ===" << endl;

    auto cartesian = PointFactory::NewCartesian(3.0f, 4.0f);
    cout << "Cartesian Point: ("
         << cartesian.getX() << ", "
         << cartesian.getY() << ")" << endl;

    auto polar = PointFactory::NewPolar(5.0f, 0.927f); // ~53 degrees
    cout << "Polar Point (r=5, θ=53°): ("
         << polar.getX() << ", "
         << polar.getY() << ")" << endl;

    return 0;
}
