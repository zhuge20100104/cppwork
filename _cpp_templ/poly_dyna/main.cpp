#include "dyna_hier.h"
#include <vector>

void draw_(geo_obj const& obj) {
    obj.draw();
}

coord distance_(geo_obj const& c1, geo_obj const& c2){
    coord c = c1.center_of_gravity() - c2.center_of_gravity();
    return c.abs();
}

void draw_elems_(std::vector<geo_obj*> const& elems) {
    for(auto const& elem_: elems) {
        elem_->draw();
    }
}

int main(int argc, char* argv[]) {
    line l {{0, 0}, {2,2}};
    circle c{{0, 0}, 1}, c1{{1,1}, 2}, c2{{0, 0}, 4};

    draw_(l);
    draw_(c);

    distance_(c1, c2);
    distance_(l, c);

    // 集合可以装异构对象
    std::vector<geo_obj*> coll;
    coll.emplace_back(&l);
    coll.emplace_back(&c);
    draw_elems_(coll);

    return EXIT_SUCCESS;
}

