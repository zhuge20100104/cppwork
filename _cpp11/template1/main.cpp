#include "funcs.hpp"
#include <iostream>

int main(int argc, char* argv[])  {
    int a{10};
    int b{5};
    int ret{Add(a, b)};

    float (*pfn) (float, float) = Add;

    std::cout << a << "+" << b << "=" << ret << std::endl;

    double arr[10] {10.1, 8.2, 9.5, 7.3, 5.2};
    auto arrSum {ArraySum(arr, 5)};
    std::cout << "Sum of arr: " << arrSum << std::endl;

    auto arrMax {Max(arr, 5)};
    std::cout << "Max of arr: " << arrMax << std::endl;

    auto arrMinMax {MinMax(arr, 5)};
    std::cout << "Min of arr: " << arrMinMax.first << std::endl;
    std::cout << "Max of arr: " << arrMinMax.second << std::endl;
}