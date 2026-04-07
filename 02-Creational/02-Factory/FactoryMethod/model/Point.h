#ifndef POINT_H
#define POINT_H

class PointFactory;  // Forward declaration

class Point {
    float x, y;

    // Private constructor — can't create Point directly!
    Point(float x, float y);

public:
    float getX() const { return x; }
    float getY() const { return y; }

    // Factory can access private constructor
    friend class PointFactory;
};

#endif // POINT_H
