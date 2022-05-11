#include "integer.h"
#include <iostream>

Integer add(Integer const& a, Integer const& b) {
    Integer temp; 
    temp.set_value(a.get_value() + b.get_value());
    return temp;
}

auto main(int argc, char** argv) -> int {
    Integer a {1}, b {3};
    a.set_value(add(a, b).get_value());
    std::cout << "add(a, b) = " << a.get_value() << "\n";
    return EXIT_SUCCESS;
}