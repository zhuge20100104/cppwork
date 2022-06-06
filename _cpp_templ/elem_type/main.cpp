#include "element.hpp"
#include <boost/type_index.hpp>

#include <iostream>
#include <cstdlib>

template <typename T>
void print_element_type(T const& c) {
    std::cout << "Container of "
        << boost::typeindex::type_id_with_cvr<typename ElementT<T>::Type>()
        << " elements.\n";
}

int main(int argc, char* argv[]) {
    std::stack<bool> s;
    print_element_type(s);

    return EXIT_SUCCESS;
}
