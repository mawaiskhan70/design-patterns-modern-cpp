#include "PointFactory.h"
#include <cmath>

Point PointFactory::NewCartesian(float x, float y) {
    return Point{ x, y };
}

Point PointFactory::NewPolar(float r, float theta) {
    return Point{ r * std::cos(theta), r * std::sin(theta) };
}
