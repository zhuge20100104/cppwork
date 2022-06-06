#include "accum6.hpp"

#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    int nums[] {1, 2, 3, 4, 5};
    std::cout << "The average value of integer values is: "
        << Accum<int>::accum(&nums[0], &nums[5]) 
        << std::endl;
    
    char const name[] = "templates";
    int length = sizeof(name);

    std::cout << "The average value of character values is: "
        << Accum<char>::accum(&name[0], &name[length])/length
        << "\n";

    return EXIT_SUCCESS;
}