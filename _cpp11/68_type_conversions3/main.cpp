#include "integer.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int {
    
    Integer i {10};
    // Integer 转int，显示转换为int
    int a = static_cast<int>(i);
    std::cout << "a= " << a << "\n";
    
    return EXIT_SUCCESS;
}