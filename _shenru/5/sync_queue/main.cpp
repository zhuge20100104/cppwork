#include "sync_queue.hpp"
#include <thread>
#include <iostream>
#include <mutex>
#include <cstdlib>

using std::cout;
using std::endl;

SyncQueue<int> syncQueue(5);

void PutDatas() {
    for(int i=0; i<20; i++) {
        syncQueue.Put(888);
    }
}

void TakeDatas() {
    int x = 0;
    for(int i=0; i<20; i++) {
        syncQueue.Take(x);
        scout << x << " ";
    }
    scout << endl;
}


int main(void) {
    std::thread t1(PutDatas);
    std::thread t2(TakeDatas);

    t1.join();
    t2.join();

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}