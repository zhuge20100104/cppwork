#include "type1.hpp"

#include <iostream>
#include <boost/type_index.hpp>

template <typename T>
void test(T const& t) {
    if(IsFounda<T>::Yes) {
        std::cout << boost::typeindex::type_id<T>() << " is founda type\n";
    } else {
        std::cout << boost::typeindex::type_id<T>() << " is no founda type\n";
    }
}

class MyType {};

int main(int argc, char* argv[]) {

    test(7);
    test(MyType());

    return EXIT_SUCCESS;
}