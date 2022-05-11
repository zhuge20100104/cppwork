#include "stack4.hpp"

#include "death_handler/death_handler.h"
#include "glog/logging.h"

#include <string>

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;

    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    try {
        Stack<int, 20> int20_stack;
        Stack<int, 40> int40_stack;
        Stack<std::string, 40> string_stack;

        int20_stack.push(7);
        LOG(INFO) << int20_stack.top() << "\n";
        int20_stack.pop();

        string_stack.push("hello");
        LOG(INFO) << string_stack.top() << "\n";
        string_stack.pop();
        string_stack.pop();

        return 0;
    } catch(std::exception const& ex) {
        LOG(ERROR) << "Exception: " << ex.what() << "\n";
        return EXIT_FAILURE;
    }
}