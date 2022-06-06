#include "sarray2_op.hpp"

#include <iostream>

int main(int argc, char* argv[]) {

    SArray<double> x(1000), y(1000);
    for(std::size_t i=0; i<1000; ++i) {
        x[i] = 1;
        y[i] = 1;
    }

    // 计算 1.2 * x + x* y
    SArray<double> tmp(x);
    tmp *= 1.2;
    x *= y;
    x += tmp;

    for(int i=0; i<20; ++i) {
        std::cout << x[i] << " ";    
    }

    std::cout <<"\n";

    return EXIT_SUCCESS;
}