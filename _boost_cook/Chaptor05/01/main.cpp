#include <boost/atomic.hpp>
#include <boost/thread/thread.hpp>

#include <iostream>

#include <cassert>

boost::atomic<int> shared_i(0);

void do_inc() {
    for(std::size_t i=0; i<30000; ++i) {
        const int i_snapshot = ++shared_i;
        (void) i_snapshot;
    }
}

void do_dec() {
    for(std::size_t i=0; i<30000; ++i) {
        const int i_snapshot = --shared_i;
        (void) i_snapshot;
    }
}

int main(int argc, char* argv[]) {
    boost::thread t1(&do_inc);
    boost::thread t2(&do_dec);

    t1.join();
    t2.join();

    assert(shared_i == 0);
    std::cout << "shared_i= " << shared_i << std::endl;
    assert(shared_i.is_lock_free());
}