#include "func.h"

#include <iostream>

int main(int argc, char* argv[]) {
    std::string src = "hello, Hello, Hello, world";
    std::string search = "Hello";

    std::vector<int> res {std::move(FindAll(src, search, Case::SENSITIVE, 0))};
    for(const auto& index: res) {
        std::cout << "index -->" << index << std::endl;
    }

    std::cout << std::endl;

    res = std::move(FindAll(src, search, Case::INSENSITIVE, 0));
    for(const auto& index: res) {
        std::cout << "index -->" << index << std::endl;
    }
}
