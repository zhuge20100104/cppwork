#include "integer.h"
#include <iostream>

class Number {
    Integer m_value {};

    public:
        Number(int value): m_value(value) {}
};


Number create_number(int num) {
    Number n {num};
    return n;
}
auto main(int argc, char** argv) -> int {
    Number n1 {1};
    auto n2 {n1};
    n2 = n1;

    auto n3 {create_number(3)};
    n3 = create_number(3);
    
    return EXIT_SUCCESS;
}