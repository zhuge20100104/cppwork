#include "dyna_hier.h"

#include <iostream>

circle::circle(coord const& center, int radius): center_{center}, radius_{radius} {}

void circle::draw() const {
    std::cout << "Circle with center: [" << center_.x << "," << center_.y << "], radius: " << radius_ 
        << std::endl; 
}

coord circle::center_of_gravity() const {
    return center_;
}

line::line(coord const& start, coord const& end): start_{start}, end_{end} {}

void line::draw() const {
    std::cout << "Line with start: [" << start_.x << "," << start_.y << "], end: ["
        << end_.x << "," << end_.y << "]." << std::endl;
}

coord line::center_of_gravity() const {
    int x = (start_.x + end_.x) / 2;
    int y = (start_.y + end_.y) / 2;
    return coord(x, y); 
}




