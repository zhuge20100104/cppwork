#include "funcs.hpp"

#include <iostream>
#include <vector>
#include <type_traits>

int main(int argc, char* argv[]) {
    auto maxFunc = [](auto x, auto y) {
        return x>y ? x:y;
    };

    auto greatorFunc = [](auto x, auto y) {
        return x>y;
    };

    auto lessFunc = [](auto x, auto y) {
        return x<y;
    };

    auto minMaxFunc = [](auto itBegin, auto ItEnd) {
        using EleType = decltype(itBegin);
        std::pair<EleType, EleType> ret{itBegin, itBegin};
        ++itBegin;
        while(itBegin != ItEnd) {
            if(*itBegin < *ret.first) {
                ret.first = itBegin;
            }

            if(*itBegin > *ret.second) {
                ret.second = itBegin;
            }
            ++itBegin;
        }
        return std::move(ret);
    };

    auto ret = Max<int>()(3,  4);
    auto retLam = maxFunc(3, 4);
    std::cout << "Max<int>()(3,  4) = " << ret << std::endl;
    std::cout << "maxFunc(3, 4) = " << retLam << std::endl; 

    auto greator = Greator<int>()(5, 4);
    auto greatorLam = greatorFunc(5, 4);
    std::cout << "Greator<int>()(5, 4) " << std::boolalpha << greator << std::endl;
    std::cout << "greatorFunc(5, 4) " << std::boolalpha << greatorLam << std::endl;

    auto less = Less<int>()(4, 5);
    auto lessLam = lessFunc(4, 5);
    std::cout << "Less<int>()(4, 5) " << std::boolalpha << less << std::endl;
    std::cout << "lessFunc(4, 5) " << std::boolalpha << lessLam << std::endl;

    std::vector<int> v {1, 3, 2, 5, 4}; 
    auto minMax = MinMax<std::vector<int>::iterator>()(v.begin(), v.end());
    auto minMaxLam = minMaxFunc(v.begin(), v.end());
    std::cout << "MinMax<std::vector<int>::iterator>() " << *(minMax.first) << " " << *(minMax.second) << std::endl;
    std::cout << "minMaxFunc(v.begin(), v.end()) " << *(minMaxLam.first) << " " << *(minMaxLam.second) << std::endl;
}