#include "integer.h"

#include <iostream>

void print(Integer val) {}

auto main(int argc, char** argv) -> int {
    Integer a {1};
    a.set_value(3);
    // 强制调用右值构造函数
    auto b {std::move(a)};
    
    Integer c {5};
    print(std::move(c));
    c.set_value(10);
    std::cout << c.get_value() << std::endl;
    return EXIT_SUCCESS;
}