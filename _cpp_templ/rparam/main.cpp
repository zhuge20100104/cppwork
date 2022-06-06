#include "rparamcls.hpp"
#include <cstdlib>

template <typename T1, typename T2>
void foo(RParamT<T1> p1, RParamT<T2> p2) {
}

int main(int argc, char* argv[]) {
    MyClass1 mc1;
    MyClass2 mc2;
    foo<MyClass1, MyClass2>(mc1, mc2);
    return EXIT_SUCCESS;
}