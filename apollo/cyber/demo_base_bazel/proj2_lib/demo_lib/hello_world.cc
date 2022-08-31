#include <iostream>
#include "hello_great.h"

int main(int argc, char* argv[]) {
    std::cout << get_great("great lib in package") << std::endl;
    return EXIT_SUCCESS;
}