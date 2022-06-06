#include <iostream>
#include <cstdlib>

// 使用宏
#define SQUARE(x) ((x)*(x))

// 内联函数
inline int square_in(int x) {
    return x * x;
}

// 普通函数
int square(int x) {
    return x * x;
}

int main(int argc, char* argv[]) {
    int val = 5;
    int result = square(val);
    std::cout << result << std::endl;

    result = SQUARE(val + 1);
    std::cout << result << std::endl;

    result = square_in(val + 1);
    std::cout << result << std::endl;

    return EXIT_SUCCESS;
}

