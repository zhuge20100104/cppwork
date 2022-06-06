#include <iostream>

// C语言的左移是循环左移，左移之后的结果为
// 33 % 32 = 1
// 左移一位
// 1111 1111 0 = 510
int main() {
    int a = 0xFF;
    int b = a << 33;
    std::cout << b << std::endl;
}


