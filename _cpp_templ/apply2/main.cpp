#include "apply2.hpp"

#include <iostream>
#include <cstdlib>

void incr(int& a) {
    ++a;
}

void print(int const& a) {
    std::cout << a << "\n";
}

int main(int argc, char* argv[]) {
    int x = 7;
    apply(x, print);
    apply(x, incr);
    apply(x, print);
    return EXIT_SUCCESS;
}