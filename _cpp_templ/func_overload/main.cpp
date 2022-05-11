#include <iostream>
#include <cstdlib>

// 优先选择更特殊的模板特化
template <typename T>
int f(T) {
    return 1;
}

template <typename T>
int f(T*) {
    return 2;
}

int main(int argc, char* argv[]) {
    std::cout << f<int*>((int*)0) << std::endl;   // 1
    std::cout << f<int>((int*)0) << std::endl;    // 2
    return EXIT_SUCCESS;
}

