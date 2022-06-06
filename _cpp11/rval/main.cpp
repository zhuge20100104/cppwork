#include <iostream>

// 返回临时值，右值
int add(int x, int y) {
    return x + y;
}

// 返回左值引用
int& transform(int &x) {
    x *= x;
    return x;
}

// 左值引用
void print(int& x) {
    std::cout << "print(int& x)" << std::endl;
}

// 常量左值引用
void print(int const& x) {
    std::cout << "print(int const& x)" << std::endl;
}

// 右值引用 
// 右值引用优先级比常量左值引用优先级高
void print(int&& x) {
    std::cout << "print(int&& x)" << std::endl;
}

int main(int argc, char* argv[]) {

    // x, y, z都是左值 
    int x = 5;
    int y = 10;
    int z = 8;

    // 表达式返回右值
    // 使用左值 result接收
    int result = (x + y) * z;

    // ++x返回左值，可以赋值
    ++x = 6;

    print(x);
    print(3);
    return EXIT_SUCCESS;
}