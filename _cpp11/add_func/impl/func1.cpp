#include "func1/func1.h"

#include <iostream>

int add(int x, int y) {
    int sum = x + y;
    std::cout << "Sum is :" << sum << std::endl;
    return sum;
}