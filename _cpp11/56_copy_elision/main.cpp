#include "integer.h"

#include <iostream>

Integer add(int a, int b) {
    Integer temp(a + b);
    return temp;
}

auto main(int argc, char** argv) -> int {
    Integer a = 3;

    Integer b = add(3, 5);
    return EXIT_SUCCESS;
}