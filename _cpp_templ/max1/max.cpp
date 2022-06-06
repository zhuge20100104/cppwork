#include "max.hpp"
#include "death_handler/death_handler.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

    Debug::DeathHandler dh;
    int i = 42;
    std::cout << "::max(7, i) " << ::max(7, i) << std::endl;

    float f1 = 3.4;
    float f2 = -6.7;
    std::cout << "::max(f1, f2) " << ::max(f1, f2) << std::endl;

    std::string s1 = "mathematics";
    std::string s2 = "math";
    std::cout << "::max(s1, s2) " << ::max(s1, s2) << std::endl; 
    return 0;
}