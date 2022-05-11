#include "integer.h"
#include <iostream>
#include <memory>

void create_integer() {
    std::unique_ptr<Integer> ele{new Integer{}};
    ele->set_value(10);
    std::cout << "create_integer: " << ele->get_value() << "\n";
}

void process(std::shared_ptr<Integer> const& ele) {
    std::cout << "process: " << ele->get_value() << "\n";
}

auto main(int argc, char* argv[]) -> int {
    create_integer();
    std::shared_ptr<Integer> i {new Integer{20}};
    process(i);
    return EXIT_SUCCESS;
}