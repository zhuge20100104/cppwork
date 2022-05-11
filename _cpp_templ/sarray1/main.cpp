#include "sarray1_ops.hpp"

#include <iostream>

#include <condition_variable>

int main(int argc, char* argv[]) {
    
    SArray<double> x(1000), y(1000);
    for(int i=0; i<x.size(); ++i) {
        x[i] = 1;
        y[i] = 1;
    }

    x = 1.2 * x + x * y;
    for(int i=0; i<20; ++i) {
        std::cout << x[i] << " ";
    }
    std::cout << "\n";

    return EXIT_SUCCESS;
}