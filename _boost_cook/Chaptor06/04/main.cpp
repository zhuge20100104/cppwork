#include "utils/tasks_processor_base.hpp"

using namespace tp_base;

// 一个全局值
int g_val = 0;

void func_test() {

    ++ g_val;
    // std::exception被捕获了，不会抛异常退出
    if(g_val == 3) {
        throw std::logic_error("Just checking");
    }
    boost::this_thread::interruption_point();
    
    // interrupted 被捕获了，不会抛异常退出 
    if(g_val == 10) {
        throw boost::thread_interrupted();
    }

    // 只有等于 90时，才会stop task
    if(g_val == 90) {
        tasks_processor::get().stop();
    }
}

int main(int argc, char* argv[]) {
    static const std::size_t tasks_count = 100;

    // 第90次时会调用stop方法
    BOOST_STATIC_ASSERT(tasks_count > 90);

    for(std::size_t i=0; i<tasks_count; ++i) {
        tasks_processor::get().push_task(&func_test);
    }

    // 也可以直接push lambda表达式
    tasks_processor::get().push_task([]() {
        std::plus<int>()(2, 2);
    });

    // 还没有启动boost::asio::io_service::run进行处理，所以为0
    assert(g_val == 0);

    tasks_processor::get().start();

    assert(g_val == 90);
}