#include "integer.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int {
    Integer a {1}, b {3};
    Integer sum = a + b;
    // 先使用，再加1，应该是4
    std::cout << (sum++).get_value() << "\n";

    if(a == b) {
        std::cout << "Same\n";
    } else {
        std::cout << "Not same\n";
    }
    
    return EXIT_SUCCESS;
}