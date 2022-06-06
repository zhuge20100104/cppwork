#include "static_hier.h"

#include <cstdlib>
#include <iostream>
#include <vector>

template <typename GeoObj> 
void draw_(GeoObj const& obj) {
    obj.draw();
}

template <typename GeoObj1, typename GeoObj2>
coord distance(GeoObj1 const& obj1, GeoObj2 const& obj2) {
    coord c = obj1.center_of_gravity() - obj2.center_of_gravity();
    return c.abs();
}

template <typename GeoObj>
void draw_elems(std::vector<GeoObj> const& elems) {
    for(auto const& ele: elems) {
        ele.draw();
    }
}

int main(int argc, char* argv[]) {
    line l{{0, 0}, {2, 2}};
    circle c{{0, 0}, 1}, c1{{1, 1}, 2}, c2{{0, 0}, 3};
    draw_(l);
    draw_(c);
    distance(c1, c2);
    distance(l, c);

    std::vector<line> col_;
    col_.emplace_back(std::move(l));
    draw_elems(col_);
    return EXIT_SUCCESS;
}