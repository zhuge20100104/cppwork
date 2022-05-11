#include "string_conv.h"

#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
    std::string src = "Hello, World";

    std::string dstUpper = ToUpper(src);
    std::string dstLower = ToLower(src);

    std::cout << "Upper: " << dstUpper << std::endl;
    std::cout << "Lower: " << dstLower << std::endl;
    return 0;
}