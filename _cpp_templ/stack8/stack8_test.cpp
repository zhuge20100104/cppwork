#include "stack8_def.hpp"

#include "glog/logging.h"
#include "death_handler/death_handler.h"

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;

    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    try {
        Stack<int> int_stack;
        Stack<float> float_stack;

        int_stack.push(42);
        int_stack.push(7);
        
        float_stack.push(7.7);

        float_stack = int_stack;

        LOG(INFO) << float_stack.top() << "\n";
        float_stack.pop();

        LOG(INFO) << float_stack.top() << "\n";
        float_stack.pop();

        LOG(INFO) << float_stack.top() << "\n";
        float_stack.pop();
    } catch(std::exception const& ex) {
        LOG(ERROR) << "Exception: " << ex.what() << "\n";
    }

    Stack<int, std::vector> v_stack;
    v_stack.push(42);
    v_stack.push(7);
    LOG(INFO) << v_stack.top() << "\n";
    v_stack.pop();
}