#include "Point.h"
#include <cmath>

Point::Point(float x, float y) : x(x), y(y) {}

// Factory implementation
Point Point::PointFactory::NewCartesian(float x, float y) {
    return Point{ x, y };
}

Point Point::PointFactory::NewPolar(float r, float theta) {
    return Point{ r * std::cos(theta), r * std::sin(theta) };
}

// Initialize static member
Point::PointFactory Point::Factory;
