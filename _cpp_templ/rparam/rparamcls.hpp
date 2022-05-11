#ifndef _FREDRIC_RPARAM_CLS_HPP_
#define _FREDRIC_RPARAM_CLS_HPP_

#include "rparam.hpp"
#include <iostream>

struct MyClass1 {
    MyClass1() {}
    MyClass1(MyClass1 const&) {
        std::cout << "MyClass1 copy constructor called\n";
    }
};

struct MyClass2 {
    MyClass2() {}
    MyClass2(MyClass2 const&) {
        std::cout << "MyClass2 copy constructor called\n";
    }
};


// MyClass2 特化，MyClass2使用值传递
template <>
struct RParam<MyClass2> {
    using Type = MyClass2;
};

template <typename T>
using RParamT = typename RParam<T>::Type;

#endif