#include "func1/func1.h"

#include <iostream>

int main(int argc, char* argv[]) {
    
    int x, y;
    std::cout << "请输入左操作数 x:";
    std::cin >> x;

    std::cout << "请输入右操作数 y:";
    std::cin >> y;

    int sum = add(x, y);
    std::cout << "add(" << x << " , " << y << ") is :" 
        << sum << std::endl;

    return 0;
}