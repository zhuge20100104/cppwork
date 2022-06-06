#include "accum4.hpp"

#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    int nums[] {1, 2, 3, 4, 5};
    std::cout << "The average value of integer values is "
        << accum(&nums[0], &nums[5]) / 5
        << "\n";

    char const name[] = "templates";
    int length = sizeof(name) - 1;
    std::cout << "The average value of character values is "
        << accum(&name[0], &name[length]) / length
        << "\n";

    return EXIT_SUCCESS;
}