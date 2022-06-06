#include "pow3.hpp"

#include <iostream>

int main(int argc, char* argv[]) {

    // 打印3的7次方
    std::cout << "Pow3<7>::result = " << Pow3<7>::result << "\n";
    return EXIT_SUCCESS;
}