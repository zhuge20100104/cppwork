#include <iostream>
#include <cstdlib>

void print(int count, char ch) {
    for(int i=0; i<count; ++i) {
        std::cout << ch;
    }
    std::cout << std::endl;
}

void exit_msg() {
    std::cout << "Exit the program" << std::endl;
}

int main(int argc, char* argv[]) {
    atexit(exit_msg);

    print(5, '#');

    void (*pfn) (int, char) = print;
    (*pfn)(10, ',');
    pfn(6 , '*');

    return EXIT_SUCCESS;
}