#include <iostream>
#include <cstdlib>

#include "base_member_pair.hpp"

// Empty Test class
class Test {};

template <typename EmptyClass> 
class Optimizable {
    public:
        BaseMemberPair<EmptyClass, void*> pair_member;
};


template <typename EmptyClass> 
class NotOptimize {
    public:
        EmptyClass e;
        void* info;
};


int main(int argc, char* argv[]) {
    std::cout << "size of Optimizable: " << sizeof(Optimizable<Test>) << "\n";
    std::cout << "size of NotOptimize: " << sizeof(NotOptimize<Test>) << "\n";
    return EXIT_SUCCESS;
}