#include "myfirst_def.hpp"

#include "glog/logging.h"
#include "death_handler/death_handler.h"

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;

    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    double ice = 3.0;
    print_typeof(ice);
    return EXIT_SUCCESS;
}