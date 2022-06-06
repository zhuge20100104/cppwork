#include <iostream>
#include <cstdlib>
#include <string>

template <typename T>
std::string f(T) {
    return "Template";
}

std::string f(int&) {
    return "Non Template";
}

int main(int argc, char* argv[]) {

    int x = 7;
    std::cout << f(x) << std::endl;
    return EXIT_SUCCESS;    
}