#include "glog/logging.h"
#include "death_handler/death_handler.h"

#include <cstring>
#include <string>

// 这个特化必须在有模板的方法前面，否则调用不到
int const& max(int const& a, int const& b) {
    return a < b? b : a;
}

template <typename T>
inline T const& max(T const& a, T const& b) {
    return a < b ? b : a;
}

template <typename T>
inline T const& max(T const& a, T const& b, T const& c) {
    return ::max(::max(a, b), c); 
}

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;

    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    LOG(INFO) << ::max(10, 30, 20) << "\n";
    
    return 0;
}