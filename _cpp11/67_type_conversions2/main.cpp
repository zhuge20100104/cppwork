#include "integer.h"
#include <iostream>

void print(Integer const& a) {}

auto main(int argc, char* argv[]) -> int {
    Integer a1 {5};
    // Integer a2 = Integer(5);
    Integer a2 = 5;
   
    // 没有相应的构造函数 Integer(char* const)所以会翻车
    // Integer a3 = "abc";

    // 这里也会调用带参构造函数，生成Integer
    print(5);

    // 先调用 移动构造函数，生成一个右值Integer，
    // 再调用 移动赋值操作符重载，将状态转移至a1
    a1 = 7;

    // 可以使用explicit 禁止隐式转换
    return EXIT_SUCCESS;
}