#include <iostream>
#include <cstdlib>

class Empty {
    using Int = int;
};

class EmptyTwo: public Empty {};

class EmptyThree: public EmptyTwo {};

int main(int argc, char* argv[]) {

    std::cout << "sizeof(Empty): "
        << sizeof(Empty) << "\n";
    
    std::cout << "sizeof(EmptyTwo): "
        << sizeof(EmptyTwo) << "\n";
    
    std::cout << "sizeof(EmptyThree): "
        << sizeof(EmptyThree) << "\n";

    return EXIT_SUCCESS;
}

