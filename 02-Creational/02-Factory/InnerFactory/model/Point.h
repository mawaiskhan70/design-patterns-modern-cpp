#ifndef POINT_H
#define POINT_H

class Point {
    float x, y;

    // Private constructor
    Point(float x, float y);

public:
    float getX() const { return x; }
    float getY() const { return y; }

    // Inner Factory — INSIDE Point class!
    class PointFactory {
    public:
        static Point NewCartesian(float x, float y);
        static Point NewPolar(float r, float theta);
    };

    // Singleton-style access to factory
    static PointFactory Factory;
};

#endif // POINT_H
