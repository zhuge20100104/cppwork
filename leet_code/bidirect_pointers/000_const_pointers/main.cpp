#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


auto main(int argc, char** argv) -> int {
    int x {1};
    int y {0};
    // 指针可以改，值也可以改
    int *p1 = &x;
    // 指针常量，指针的指向可以改，指针指向的值不能改
    int const* p2 = &x;
    //  常量指针，指针的指向不可改，指针指向的值可以改
    int *const p3 = &x;
    // 既是指针常量，又是常量指针，指针的指向不能改，指针指向的值也不能改
    int const* const p4 = &x;
    return EXIT_SUCCESS;
}