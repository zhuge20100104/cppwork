#include <iostream>
#include <future>
#include <chrono>

using std::cout;
using std::endl;
#include <cstdlib>

void TestAsync() {
    std::future<int> f1 = std::async(std::launch::async, []{
        return 8;
    });

    cout << f1.get() << endl;

    std::future<void> f2 = std::async(std::launch::async, [] {
        cout << 8 << endl;
        return;
    });

    f2.wait();

    std::future<int> f3 = std::async(std::launch::async, [] {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 8;
    });

    cout << "waiting..." << endl;
    std::future_status status;

    do{
        status = f3.wait_for(std::chrono::seconds(1));
        if(status == std::future_status::deferred) {
            cout << "defered" << endl;
        } else if(status == std::future_status::timeout) {
            cout << "timeout" << endl;
        } else if(status == std::future_status::ready) {
            cout << "ready" << endl;
        } 
    } while(status != std::future_status::ready);
    cout << "result is: " << f3.get() << endl;
}

int main(void) {
    TestAsync();

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}