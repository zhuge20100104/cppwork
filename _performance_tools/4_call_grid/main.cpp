#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
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
    f();
    printf("process is over!\n");
    return EXIT_SUCCESS;
}