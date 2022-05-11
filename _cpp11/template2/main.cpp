#include "funcs.hpp"
#include <iostream>

int main(int argc, char* argv[])  {

    int a{10};
    int b{5};
    int ret{Add(a, b)};

    float (*pfn) (float, float) = Add;

    std::cout << a << "+" << b << "=" << ret << std::endl;

    double arr[5] {10.1, 8.2, 9.5, 7.3, 5.2};
    double arrSum {};
    ArraySum(arr, arrSum);
    std::cout << "Sum of arr: " << arrSum << std::endl;

    auto arrMax {Max(arr)};
    std::cout << "Max of arr: " << arrMax << std::endl;

    auto arrMinMax {MinMax(arr)};
    std::cout << "Min of arr: " << arrMinMax.first << std::endl;
    std::cout << "Max of arr: " << arrMinMax.second << std::endl;

    char* arrStr[]  {"B", "A", "C", "D", "E"};
    std::shared_ptr<char> sChArrSum {new char[20], std::default_delete<char[]>()};
    char* chArrSum =  sChArrSum.get();
    ArraySum(arrStr, chArrSum);
    std::cout << "Sum of arr: " <<  chArrSum << std::endl;

    auto chArrMax {Max(arrStr)};
    std::cout << "Max of arr: " << chArrMax << std::endl;

    auto chArrMinMax {MinMax(arrStr)};
    std::cout << "Min of arr: " << chArrMinMax.first << std::endl;
    std::cout << "Max of arr: " << chArrMinMax.second << std::endl;


    std::string strStdArr[] {"B", "A", "C", "D", "E"};
    std::string resStr {};
    ArraySum(strStdArr, resStr);
    std::cout << "Sum of arr: " << resStr << std::endl;

    std::string strArrMax {Max(strStdArr)};
    std::cout << "Max of arr: " << strArrMax << std::endl;

    auto strArrMinMax {MinMax(strStdArr)};
    std::cout << "Min of arr: " << strArrMinMax.first << std::endl;
    std::cout << "Max of arr: " << strArrMinMax.second << std::endl;
    
    return 0;
}