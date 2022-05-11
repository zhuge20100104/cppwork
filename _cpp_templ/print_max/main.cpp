#include "my_class.hpp"

#include <vector>
#include <list>
#include <algorithm>

template <typename T>
void print_max(T const& col_) {
    using iter_type = typename T::const_iterator;
    iter_type const& pos = std::max_element(col_.begin(), col_.end());
    if(pos != col_.end()) {
        std::cout << *pos << std::endl;
    } else {
        std::cout << "empty" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::vector<my_class> v {{1}, {2}, {3}};
    std::list<my_class>  l {{1}, {2}, {4}, {5}};

    print_max(v);
    print_max(l);
    return EXIT_SUCCESS;
}