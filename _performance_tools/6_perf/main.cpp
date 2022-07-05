#include <iostream>
#include <chrono>
#include <thread>


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
    for(int i=0; i<5; ++i) {
        f();
    }
    std::cout << "process is over!" << std::endl;
    return EXIT_SUCCESS;
}