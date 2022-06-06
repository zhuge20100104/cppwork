#include "sizeof_.hpp"

#include <iostream>

int main(int argc, char* argv[]) {

    std::cout << "size of int is: "
        << type_size<int>::value
        << "\n";

    return EXIT_SUCCESS;
}