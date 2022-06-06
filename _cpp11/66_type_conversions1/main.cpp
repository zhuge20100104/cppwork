#include <iostream>

auto main(int argc, char** argv) -> int {
    int a = 5, b = 3;
    float c = static_cast<float>(a)/b;
    std::cout << "c= " << c << "\n";
    // static_cast int* 转 char* 会失败，会做类型检查
    // char* ch = static_cast<char*>(&a);

    // reintepret_cast也可以做这种转换，但你要清楚自己在干啥
    // reintepret_cast会保留 const volatile这些修饰符
    char* ch = reinterpret_cast<char*>(&a);
    std::cout << "ch= " << ch << "\n";

    // 使用reintepret_cast将 const int*转换为 int*会失败
    // 因为丢失了 const 限定符
    const int d = 5;
    // int* e = reinterpret_cast<int*>(&d);

    // 可以用const_cast将 const 限定符去掉
    int* e = const_cast<int*>(&d);
    
    std::cout << "*e= " << *e << "\n";
    return EXIT_SUCCESS;
}