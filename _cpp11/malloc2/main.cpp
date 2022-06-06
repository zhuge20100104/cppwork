#include <iostream>

void test_new() {
    int* p = new int(5);
    std::cout << *p << std::endl;
    delete p;
    p = nullptr;
}

int main(int argc, char* argv[]) {
    test_new();
    return EXIT_SUCCESS;
}