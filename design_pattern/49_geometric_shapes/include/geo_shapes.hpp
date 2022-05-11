#ifndef _FREDRIC_GEO_SHAPES_HPP_
#define _FREDRIC_GEO_SHAPES_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <concepts>

template <typename T>
concept Drawable = requires (T value) {
    value.draw();
};

struct Circle {
    void draw() {
        std::cout << "circle" << std::endl;
    }
};

template <Drawable DrawT>
struct Group {
    std::string name;
    std::vector<DrawT> objects;
    
    Group(std::string const& name_): name{name_} {}
    void draw() {
        std::cout << "Group " << name << " contains: " << std::endl;
        for(auto&& o: objects) {
            o.draw();
        }
    }
};

#endif