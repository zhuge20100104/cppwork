#include "integer.h"
#include <iostream>

std::istream& operator >> (std::istream& is, Integer &a) {
    int x;
    std::cin >> x;
    *a.m_pint = x;
    return is;
}

auto main(int argc, char* argv[]) -> int {
    Integer a;
    std::cout << "请输入a的值: \n";
    std::cin >> a;
    std::cout << a.get_value() << "\n";
    return EXIT_SUCCESS;
}