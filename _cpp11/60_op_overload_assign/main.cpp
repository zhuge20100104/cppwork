#include "integer.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int {
    
    Integer a {1}, b {3};
    Integer c; 
    c = a;

    std::cout << c.get_value() << "\n";
    a = a;
    std::cout << a.get_value() << "\n";
    
    return EXIT_SUCCESS;
}