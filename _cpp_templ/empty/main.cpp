#include <iostream>
#include <cstdlib>

class EmptyClass {};

int main(int argc, char* argv[]) {

    std::cout << "sizeof(EmptyClass): " << sizeof(EmptyClass) 
        << "\n";

    return EXIT_SUCCESS;
}