#include "stack3.hpp"

#include "death_handler/death_handler.h"
#include "glog/logging.h"

#include <deque>

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;

    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    try {
        Stack<int> int_stack;
        int_stack.push(7);
        LOG(INFO) << int_stack.top() << "\n";
        int_stack.pop();

        Stack<double, std::deque<double>> dbl_stack;
        dbl_stack.push(42.42);
        LOG(INFO) << dbl_stack.top() << "\n";
        dbl_stack.pop();
        dbl_stack.pop();
        
        return 0;
    } catch(std::exception const& ex) {
        LOG(ERROR) << "Exception: " << ex.what() << "\n";
        return EXIT_FAILURE;
    }
}