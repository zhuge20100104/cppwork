#include <iostream>
using std::cout;
using std::endl;

#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib>

std::timed_mutex mutex;

using timeMillSeconds = std::chrono::milliseconds;

void work() {
    timeMillSeconds time_out(100);
    while(true) {
        if(mutex.try_lock_for(time_out)) {
            cout << std::this_thread::get_id() << ": do work with the mutex" << endl;
            timeMillSeconds sleepDuration(250);
            std::this_thread::sleep_for(sleepDuration);
            mutex.unlock();
            std::this_thread::sleep_for(sleepDuration);
        } else {
            cout << std::this_thread::get_id() << ": do work without the mutex" << endl;
            timeMillSeconds sleepDuration(100);
            std::this_thread::sleep_for(sleepDuration);
        }
    }
}

int main(void) {
    std::thread t1(work);
    std::thread t2(work);

    t1.join();
    t2.join();

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}