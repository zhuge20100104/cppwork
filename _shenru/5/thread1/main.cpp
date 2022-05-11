#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
using std::cout;
using std::endl;

std::mutex g_lock;

void func() {
    g_lock.lock();
    cout << "Enter thread: " << std::this_thread::get_id() << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "Leave thread: " << std::this_thread::get_id() << endl;
    g_lock.unlock();
}

int main(void) {
    std::thread t1(func);
    std::thread t2(func);
    std::thread t3(func);

    t1.join();
    t2.join();
    t3.join();

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}