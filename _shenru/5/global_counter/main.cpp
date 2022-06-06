#include <iostream>
#include <thread>
#include <mutex>
#include <cstdlib>

using std::cout;
using std::endl;

struct Counter {
    int value = 0;
    std::mutex mutex;

    void increment() {
        std::lock_guard<std::mutex> lock(mutex);
        ++value;
        cout << value << endl;
    }

    void decrement() {
        std::lock_guard<std::mutex> lock(mutex);
        --value;
        cout << value << endl;
    }

    int get() {
        return value;
    }
};


Counter g_counter;

void Increments() {
    for(int i=0; i<10; ++i) {
        g_counter.increment();
    }
}

void Decrements() {
    for(int i=0; i<5; ++i) {
        g_counter.decrement();
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