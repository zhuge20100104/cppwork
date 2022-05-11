#include "utils/tasks_processor_multithread.hpp"

#include <boost/thread/barrier.hpp>

using namespace tp_multithread;

const std::size_t threads_count = 5;

boost::barrier g_barrier(threads_count);

void multithread_test() {
    g_barrier.wait();
    tasks_processor::get().stop();
}

int main(int argc, char* argv[]) {
    for(std::size_t i=0; i<threads_count; ++i) {
        tasks_processor::get().push_task(&multithread_test);
    }

    time_t t1 = time(nullptr);
    tasks_processor::get().start_multiple(threads_count);
    time_t t2 = time(nullptr);
    // 1秒钟的延时是因为ios_service和os delay
    assert(t2 - t1 < 1);

}
