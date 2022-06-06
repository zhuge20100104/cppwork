#ifndef _FREDRIC_POINT_H_
#define _FREDRIC_POINT_H_
#include <cmath>
#include <iostream>

class Point {
    Point(float const x_, float const y_): x{x_}, y{y_} {}

public:
    float x, y;

    friend std::ostream& operator<<(std::ostream& os, Point const& obj) {
        return os <<
            "x: " << obj.x <<
            " y: " << obj.y;
    }

    static Point NewCartision(float x, float y) {
        return {x, y};
    }

    static Point NewPolar(float r, float theta) {
        return {r*cos(theta), r*sin(theta)};
    }
};
#endif