#include "string_find.h"

#include <iostream>

int main(int argc, char* argv[]) {
    std::string src {"Hello, World"};
    std::string search {"WORLD"};

    auto pos = Find(src, search, Case::SENSITIVE, 0);
    if(pos == std::string::npos) {
        std::cout << "未找到dest string" << std::endl;
    } else {
        std::cout << "找到dest string, 位置在: " << pos << std::endl;
    }

    pos = Find(src, search, Case::INSENSITIVE, 0);
     if(pos == std::string::npos) {
        std::cout << "未找到dest string" << std::endl;
    } else {
        std::cout << "找到dest string, 位置在: " << pos << std::endl;
    }
    return 0;
}