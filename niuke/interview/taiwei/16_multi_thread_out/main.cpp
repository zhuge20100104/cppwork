#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <atomic>
#include <thread>

using namespace std;

atomic<bool> is_writed(false);

void func1() {
    for(int i=1; i<=100; ++i) {
        while(is_writed);
        if(!is_writed) {
            printf("Thread 1: %d\n", i);
            is_writed = !is_writed;
        }        
    }
}

void func2() {
    for(int i=1; i<=100; ++i) {
        while(!is_writed);
        if(is_writed) {
            printf("Thread 2: %d\n", i);
            is_writed = !is_writed;
        }
    }
}

int main(int argc, char* argv[]) {  
    std::thread t1(func1);
    std::thread t2(func2);

    t1.join();
    t2.join();
    return EXIT_SUCCESS;
}