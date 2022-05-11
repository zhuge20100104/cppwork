#include "integer.h"

#include <iostream>

int main(int argc, char* argv[]) {
    Inetger i1;
    // 拷贝构造函数被禁止，不能使用
    // Inetger i2{i1};
    i1.set_value(10);

    // 不允许设置浮点数
    // i1.set_value(11.2f);

    std::cout << i1.get_value() << std::endl;
    
    return EXIT_SUCCESS;
}