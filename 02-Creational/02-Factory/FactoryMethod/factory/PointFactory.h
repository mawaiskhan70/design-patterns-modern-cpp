#ifndef POINT_FACTORY_H
#define POINT_FACTORY_H

#include "Point.h"

class PointFactory {
public:
    static Point NewCartesian(float x, float y);
    static Point NewPolar(float r, float theta);
};

#endif // POINT_FACTORY_H
