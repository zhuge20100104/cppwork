#include "utils/tasks_processor_timer.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>

using namespace tp_timers;

void test_func(int &i) {
    i = 1;
    tasks_processor::get().stop();
}

void test_func1() {
    throw std::logic_error("It works!");
}

int main(int argc, char* argv[]) {
    const int seconds_to_wait = 3;

    int i = 0;

    // 3秒之后改变 i值，并停止tasks
    tasks_processor::get().run_after(
        boost::posix_time::seconds(seconds_to_wait),
        [&i](){
            test_func(i);
        });

    // 1秒之后run test_func1
    tasks_processor::get().run_at(
        boost::posix_time::from_time_t(time(nullptr) + 1),
        []() {
            test_func1();
        }
    );

    //  先记一下起始时间
    int t1 = static_cast<int>(time(nullptr));
    // 未启动task i=0
    assert(i == 0);
    // 启动 task,并等待task完成
    tasks_processor::get().start();
    // task完成之后 i==1
    assert(i == 1);
    int t2 = static_cast<int>(time(nullptr));
    assert(t2 - t1 >= seconds_to_wait);
}