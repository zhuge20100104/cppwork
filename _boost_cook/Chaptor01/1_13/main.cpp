#include <iostream>
#include <typeinfo>
#include <boost/type_index.hpp>

template <class T>
void do_something(const T& x) {
    // std RTTI
    std::cout << "T is " << typeid(T).name() << std::endl;
    // supress unused warning
    (void)x;
}

void sample1() {
    auto&& x = 42;
    std::cout << "x is "
        << typeid(decltype(x)).name()
        << std::endl;
    // supress unused warning
    (void)x;
}

template <class T>
void do_something_with_boost(const T& x) {
    std::cout << "T is " << boost::typeindex::type_id<T>() << std::endl;
    (void)x;
}

void sample2_with_boost() {
    auto&& x = 42;
    std::cout << "x is "
        << boost::typeindex::type_id_with_cvr<decltype(x)>()
        << std::endl;
}

int main(int argc, char* argv[]) {
    do_something(1.0);
    sample1();
    do_something_with_boost(1.0);
    sample2_with_boost();
}











