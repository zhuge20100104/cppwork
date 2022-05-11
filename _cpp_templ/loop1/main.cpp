#include "loop1.hpp"

#include <iostream>

int main(int argc, char* argv[]) {

    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};

    std::cout << "dot_product(3, a, b) = " << dot_product(3, a, b) << "\n";
    return EXIT_SUCCESS;
}