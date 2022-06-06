#include <iostream>
#include <cstdlib>

class Empty {
    public:
        using Int = int;
};

class EmptyTwo: public Empty {};

class NonEmpty: public Empty, public EmptyTwo {};

int main(int argc, char* argv[]) {

    Empty e;
    EmptyTwo e_2;
    NonEmpty ne;
    std::cout << "size of Empty: " << sizeof(Empty) << "\n";
    std::cout << "size of EmptyTwo: " << sizeof(EmptyTwo) << "\n";
    std::cout << "size of NonEmpty: " << sizeof(NonEmpty) << "\n";
    return EXIT_SUCCESS;
}
