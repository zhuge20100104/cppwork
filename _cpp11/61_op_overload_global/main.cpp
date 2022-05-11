#include "integer.h"
#include <iostream>

Integer operator+(int a, Integer const& b) {
    Integer temp;
    temp.set_value(a + b.get_value());
    return temp;
}

std::ostream& operator<<(std::ostream& os, Integer const& i) {
    os << i.get_value();
    return os;
}

std::istream& operator>>(std::istream& is, Integer& a) {
    int x;
    is >> x;
    a.set_value(x);
    return is;
}

auto main(int argc, char* argv[]) -> int {
    
    Integer a {3}, b {1};
    
    auto c = 1 + a;
    std::cout << "c= " << c << "\n";
    
    std::cout << "请输入Integer d的值: ";
    Integer d;
    std::cin >> d;
    std::cout << "d= " << d << "\n";
    return EXIT_SUCCESS;
}