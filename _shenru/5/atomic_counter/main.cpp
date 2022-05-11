#include <iostream>
#include <atomic>
#include <thread>
#include <cstdlib>

using std::cout;
using std::endl;

struct Counter {
    std::atomic<int> value {0};
    
    void increment() {
        ++ value;
    }

    void decrement() {
        -- value;
    }

    int get() {
        return value;
    }
};


Counter g_counter;

void Increments() {
    for(int i=0; i<10; ++i) {
        g_counter.increment();
        cout << g_counter.get() << endl;
    }
} 

void Decrements() {
    for(int i=0; i<5; ++i) {
        g_counter.decrement();
        cout << g_counter.get() << endl;
    }
}


int main(void) {
    std::thread t1(Increments);
    std::thread t2(Decrements);

    t1.join();
    t2.join();

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}