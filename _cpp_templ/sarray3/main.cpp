#include "exprops2.hpp"

#include <iostream>

int main(int argc, char* argv[]) {

    Array<double> a(1000), b(1000);
    for(std::size_t i=0; i<1000; ++i) {
        a[i] = 1;
        b[i] = 1;
    }

    a = 1.2 * a + b;

    for(std::size_t i=0; i<20; ++i) {   
        std::cout << a[i] << " ";
    }

    std::cout << "\n";
    
    return EXIT_SUCCESS;
}