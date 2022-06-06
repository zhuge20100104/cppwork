#ifndef _FREDRIC_SINGLETON_DI_HPP_
#define _FREDRIC_SINGLETON_DI_HPP_
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <concepts>

template <typename T>
concept FooType = requires (T value) {
    {value.name()} -> std::convertible_to<std::string>;
};

struct Foo {
    static int id;
    Foo() { ++id; }
    std::string name() {
        return "foo " + std::to_string(id);
    }
};

int Foo::id = 0;

template <FooType FooT>
struct Bar {
    std::shared_ptr<FooT> foo;
};
#endif