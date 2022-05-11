#include <iostream>
#include <cstdlib>

int sum(int x, int y) {
    return x + y;
}

int main(int argc, char* argv[]) {
    auto i =10;
    auto j = 5;
    auto sum_ = i + 4.3f;

    auto result = sum(i, j);

    // static 和 const 可以修饰auto
    static auto y = 2;

    const int x = 10;

    const auto var = x;  // 直接赋值变量，必须指定const，否则const丢失
    auto& var_ref = x;
    auto var_ptr = &x;   // 引用和指针不需要，可以直接继承 const

    auto lis = {1, 2, 3, 4}; // 初始化列表赋值，需要写在右边，直接跟在auto 后面可能就是int
    return EXIT_SUCCESS;
}