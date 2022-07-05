#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cstdio>

void test() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void f() {
    int i;
    for(i=0; i<5; ++i) {
        test();
    }
}
int main(int argc, char* argv[]) {
    f();
    std::cout << "Process is over" << std::endl;
    return EXIT_SUCCESS;
}