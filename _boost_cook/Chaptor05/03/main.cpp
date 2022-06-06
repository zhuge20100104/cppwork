// 在前面的模块中，我们都是引入boost/thread.hpp，
// 这样将会引入 Boost.Thread模块的所有类
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

#include <iostream>

#include <cassert>
#include <cstddef>

// 不做同步的名称空间
namespace without_sync {
    int shared_i = 0;

    void do_inc() {
        for(std::size_t i=0; i<30000; ++i) {
            int i_snapshot = ++shared_i;
            (void) i_snapshot;
        }
    }

    void do_dec() {
        for(std::size_t i=0; i<30000; ++i) {
            int i_snapshot = --shared_i;
            (void) i_snapshot;
        }
    }

    void run() {
        boost::thread t1(&do_inc);
        boost::thread t2(&do_dec);

        t1.join();
        t2.join();

        std::cout << "in without_sync, shared_i= " << shared_i << std::endl;
    }
};

// 做同步的名称空间
namespace  with_sync{
    int shared_i = 0;
    boost::mutex i_mutex;

    void do_inc() {
        for(std::size_t i=0; i<30000; ++i) {
            int i_snapshot;
            {
                boost::lock_guard<boost::mutex> lock(i_mutex);
                i_snapshot = ++shared_i;
            }
            (void) i_snapshot;
        }
    }

    void do_dec() {
        for(std::size_t i=0; i<30000; ++i) {
            int i_snapshot;
            {
                boost::lock_guard<boost::mutex> lock(i_mutex);
                i_snapshot = --shared_i;
            }
            (void) i_snapshot; 
        }
    }

    void run() {
        boost::thread t1(&do_inc);
        boost::thread t2(&do_dec);

        t1.join();
        t2.join();

        assert(shared_i == 0);
        std::cout << "in with_sync, shared_i= " << shared_i << std::endl;
    }
} // namespace  with_sync


int main(int argc, char* argv[]) {
    without_sync::run();
    std::cout << std::endl;
    with_sync::run();
    std::cout << std::endl;
}