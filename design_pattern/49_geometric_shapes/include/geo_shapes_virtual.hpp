#ifndef _FREDRIC_GEO_SHAPES_VIRTUAL_HPP_
#define _FREDRIC_GEO_SHAPES_VIRTUAL_HPP_

#include <iostream>
#include <string>
#include <vector>

struct GraphicBaseV {
    virtual void draw() = 0;
};

struct CircleV: GraphicBaseV {
    void draw() override {
        std::cout << "circle" << std::endl;
    }
};


struct GroupV: GraphicBaseV {
    std::string name;
    std::vector<GraphicBaseV*> objects;

    GroupV(std::string const& name_): name{name_} {}

    void draw() {
        std::cout << "Group " << name << " contains: " << std::endl;
        for(auto&& o: objects) {
            o->draw();
        }
    }
};
#endif