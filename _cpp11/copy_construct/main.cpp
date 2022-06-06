#include "integer.h"

#include <iostream>

int main(int argc, char* argv[]) {
    Integer i1 {1};
    Integer i2 {i1};

    std::cout << i1.get_value() << std::endl;
    std::cout << i2.get_value() << std::endl;

    i2.set_value(2);
    std::cout << i1.get_value() << std::endl;
    std::cout << i2.get_value() << std::endl;

    Integer i3 = std::move(i1);
    // move 之后变成 null_ptr，再解引用会崩。
    // std::cout << i1.get_value() << std::endl;
    std::cout << i2.get_value() << std::endl;
    std::cout << i3.get_value() << std::endl;
    return EXIT_SUCCESS;
}
