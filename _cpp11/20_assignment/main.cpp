#include "funcs.h"

#include <iostream>

int main(int argc, char* argv[]) {
    int a = 1;
    int b = 2;
    int c = Add(&a, &b);
    std::cout << a << " + " << b << " = " << c << std::endl;

    int result = 0;
    AddVal(&a, &b, &result);
    std::cout << a << " + " << b << " = " << result << std::endl;

    Swap(&a, &b);
    std::cout << "After swap, a= " << a <<", b=" << b << std::endl;

    int k = 4;
    int fact_res = 1;
    Factorial(&k, &fact_res);
    std::cout << k << "! = " << fact_res << std::endl;

    return 0;
}