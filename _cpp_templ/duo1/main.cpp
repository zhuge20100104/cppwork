#include "duo1/duo1.hpp"

#include <iostream>

Duo<float, int> foo() {
    return make_duo(42.0f, 42);
}

int main(int argc, char* argv[]) {
    if(foo() == make_duo(42, 42.0f)) {
        std::cout << "Two duos are equal..." << std::endl;
    } else {
        std::cout << "Two duos are not equal..." << std::endl;
    }
    
    return EXIT_SUCCESS;
}