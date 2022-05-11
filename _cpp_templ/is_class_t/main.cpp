#include "is_class_t.hpp"

#include <iostream>
#include <cstdlib>

class MyClass {};

struct MyStruct {};

union MyUnion {};

void my_func() {}

enum E {e1 } e;

template <typename T>
void check() {
    if(IsClassT<T>::YES) {
        std::cout << "IsClassT\n";
    } else {
        std::cout << "!IsClassT\n";
    }
}

template <typename T>
void checkT(T) {
    check<T>();
}

int main(int argc, char* argv[]) {
    std::cout << "int: ";
    check<int>();

    std::cout << "MyClass: ";
    check<MyClass>();

    std::cout << "MyStruct: ";
    MyStruct s;
    checkT(s);

    std::cout << "MyUnion: ";
    check<MyUnion>();

    std::cout << "enum: ";
    checkT(e);

    std::cout << "myfunc(): ";
    checkT(my_func);
    return EXIT_SUCCESS;
}