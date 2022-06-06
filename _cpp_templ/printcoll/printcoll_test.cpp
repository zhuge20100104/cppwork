#include "printcoll.hpp"

#include "death_handler/death_handler.h"

#include <vector>

int main(int argc, char* argv[]) {

    Debug::DeathHandler dh;

    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    std::vector<int> v;
    v.push_back(42);
    v.push_back(13);
    v.push_back(7);
    printcoll(v);
}