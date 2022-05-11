#include <boost/tuple/tuple.hpp>

#include <iostream>

template <int N>
struct printer {
    printer() {
        std::cout << N << " ";        
    }
};

int main(int argc, char* argv[]) {
    boost::tuple<printer<0>, printer<1>, printer<2> > t;
    (void)t;
    return 0;
}