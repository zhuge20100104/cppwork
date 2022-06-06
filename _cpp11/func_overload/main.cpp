#include <iostream>
#include <cstdlib>

extern "C" int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

void print(float x) {
    std::cout << "print(float)"<< std::endl;
    std::cout << x << std::endl;
}

void print(int const* x) {
    std::cout << "print(int const*)"<< std::endl;
    std::cout << *x << std::endl;
}

extern "C" void print(int const& x) {
    std::cout << "print(int const&)"<< std::endl;
    std::cout << x << std::endl;
}

int main(int argc, char* argv[]) {
    int result = add(3, 5);

    std::cout << "add(int, int) add(3, 5) = " << result << std::endl;

    double result_double = add(3.1, 6.2);
    std::cout << "add(double, double) add(3.1, 6.2) = " << result_double << std::endl;

    int x = 19;
    print(x);


    return EXIT_SUCCESS;
}