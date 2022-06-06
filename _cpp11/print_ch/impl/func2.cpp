#include "func2/func2.h"

#include <iostream>

void print(const char ch, const size_t n) {
    for(size_t i=0; i<n; ++i) {
        std::cout << ch;
    }
    std::cout << std::endl;
}