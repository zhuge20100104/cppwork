#include <iostream>
#include <cstdlib>

template <int N>
class X {
    public:
        typedef int I;
        void f(int i) {
            std::cout << "X<N>::f(int) = " << i << std::endl;
        }
};

template <int N>
void fppm(void (X<N>::*p)(typename X<N>::I),X<N>& x, typename X<N>::I i) {
   (x.*p)(i);
}

int main(int argc, char* argv[]) {
    X<33> x;
    fppm(&X<33>::f, x, 3);
    return EXIT_SUCCESS;
}