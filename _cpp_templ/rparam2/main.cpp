#include "rparam/rparamcls.hpp"

#include <cstdlib>

template <typename T1, typename T2>
void foo_core(RParamT<T1> p1, RParamT<T2> p2) {}

template <typename T1, typename T2>
void foo(T1 const& p1, T2 const& p2) {
    foo_core<T1, T2>(p1, p2);
}

int main(int argc, char* argv[]) {

    MyClass1 mc1;
    MyClass2 mc2;

    foo(mc1, mc2);
    return EXIT_SUCCESS;
}