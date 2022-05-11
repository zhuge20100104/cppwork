#include "stack2.hpp"

#include "death_handler/death_handler.h"
#include "glog/logging.h"

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;

    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    try {
        Stack<int> int_stack;
        Stack<std::string> string_stack;

        int_stack.push(7);
        LOG(INFO) << int_stack.top() << "\n";
        int_stack.pop();

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