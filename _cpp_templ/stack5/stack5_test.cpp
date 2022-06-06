#include "stack5_def.hpp"

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
        Stack<float> float_stack;

        int_stack.push(42);
        int_stack.push(7);

        float_stack.push(7.7);

        float_stack = int_stack;

        LOG(INFO) << float_stack.top();
        float_stack.pop();

        LOG(INFO) << float_stack.top();
        float_stack.pop();

        LOG(INFO) << float_stack.top();
        float_stack.pop();

        return 0;
    } catch(std::exception const& ex) {
        LOG(ERROR) << "Exception: " << ex.what();
        return EXIT_FAILURE;
    }
}