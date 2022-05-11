#include "utils/tasks_processor_signal.hpp"

using namespace tp_full;

void accept_3_signals_and_stop(int signal) {
    static int signal_count = 0;

    assert(signal == SIGINT);
    ++ signal_count;

    std::cerr << "Captured " << signal_count << "SIGINT\n";
    if(signal_count == 3) {
        tasks_processor::get().stop();
    }
}

int main(int argc, char* argv[]) {
    // 注册的时候表示可以捕获 1和SIGINT两种信号
    // 捕获以后使用 accept_3_signals_and_stop 函数进行处理
    tasks_processor::get().register_signals_handler(
        &accept_3_signals_and_stop,
        std::vector<int>(1, SIGINT)
    );

    // 实际运行时只可能发送SIGINT信号，1是发不了的
    // Ctrl + C发送SIGINT
    tasks_processor::get().start();
}