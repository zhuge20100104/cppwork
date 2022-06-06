#include "funcs.h"

#include <iostream>

int main(int argc, char* argv[]) {
    int add_res {0};
    Add(3, 5, add_res);
    std::cout << 3 << " + " << 5 << " = " << add_res << std::endl;
    int fact_res {1};
    Factorial(4, fact_res);
    std::cout << "4!= " << fact_res << std::endl;
     int a {1};
    int b {2};
    Swap(a, b);
    std::cout << "After swap: a= " << a << " b= " << b << std::endl;
    return 0;
}