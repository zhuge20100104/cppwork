#include "typet.hpp"

#include <iostream>

class MyClass {};

void myfunc() {}

enum E {e1};


// 使用类型调用
template <typename T>
void check() {
    if(TypeT<T>::IsFundaT) {
        std::cout << "IsFundaT";
    }else if(TypeT<T>::IsPtrT) {
        std::cout << "IsPtrT";
    }else if(TypeT<T>::IsRefT) {
        std::cout << "IsRefT";
    }else if(TypeT<T>::IsArrayT) {
        std::cout << "IsArrayT";
    }else if(TypeT<T>::IsFuncT) {
        std::cout << "IsFuncT";
    }else if(TypeT<T>::IsPtrMemT) {
        std::cout << "IsPtrMemT";
    }else if(TypeT<T>::IsEnumT) {
        std::cout << "IsEnumT";
    }else if(TypeT<T>::IsClassT) {
        std::cout << "IsClassT";
    }
    std::cout << std::endl;
}

// 使用实例调用
template <typename T>
void checkT(T) {
    check<T>();
    // 指针类型打印基础类型
    if(TypeT<T>::IsPtrT || TypeT<T>::IsPtrMemT) {
        check<typename CompondT<T>::BaseT>();
    }
}

int main(int argc, char* argv[]) {
    std::cout << "int:" << std::endl;
    check<int>();

    std::cout << "int&:" << std::endl;
    check<int&>();

    std::cout << "char[42]:" << std::endl;
    check<char[42]>();

    std::cout << "MyClass:" << std::endl;
    check<MyClass>();

    std::cout << "ptr to enum:" << std::endl;
    E* ptr = 0;
    checkT(ptr);

    std::cout << "42:" << std::endl;
    checkT(42);

    std::cout << "myfunc():" << std::endl;
    checkT(myfunc);

    std::cout << "memptr to array:" << std::endl;
    char (MyClass::* memptr) [] = 0;
    checkT(memptr);
    return EXIT_SUCCESS;
}