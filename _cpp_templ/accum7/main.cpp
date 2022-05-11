#include "accum7.hpp"
#include "mul_policy.hpp"

#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {

    int nums[] {1, 2, 3, 4, 5};

    std::cout << "The average value of the integer value is: "
        << SumAccum<int, 15>::accum(&nums[0], &nums[5]) / 5
        << "\n";

    std::cout << "The product of integer values is: "
        << MulAccum<int>::accum(&nums[0], &nums[5])
        << "\n";

    char const name[] = "templates";
    int length = sizeof(name)-1;

    std::cout << "The average value of the character values is: "
        << SumAccum<char>::accum(&name[0], &name[length]) / length
        << std::endl;

    return EXIT_SUCCESS;
}