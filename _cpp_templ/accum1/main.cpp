#include "accum1.hpp"

#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    int nums[] = {1, 2, 3, 4, 5};
    std::cout << "The average value of the integer values is: "
        << accum(&nums[0], &nums[5])/5
        <<"\n";

    char const name[] = "templates";   // char[] 变量出错, overflow
    int length = sizeof(name)-1;

    std::cout << "The average value of the characters values is : "
        << accum(&name[0], &name[length])/length
        << "\n";

    return EXIT_SUCCESS;
}


