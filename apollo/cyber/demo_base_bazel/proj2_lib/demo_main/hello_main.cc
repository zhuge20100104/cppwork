#include <iostream>
#include "demo_lib/hello_great.h"

int main(int argc, char* argv[]) {
    std::cout << get_great("hello lib out package") << std::endl;
    return EXIT_SUCCESS;
}