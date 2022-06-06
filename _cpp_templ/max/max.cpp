#include "glog/logging.h"
#include "death_handler/death_handler.h"

template <typename T>
inline T const& max(T const& a, T const& b) {
    return a < b? b: a;
}

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    LOG(INFO) << ::max<double>(1.1, -3.0);  // 显示指定为double
    LOG(INFO) << ::max(1.1, -3.0);   // 隐式推导为double
    LOG(INFO) << ::max<int>(1.1, -3.0); // 显示指定为int，将会返回1，去掉小数点

    return EXIT_SUCCESS;
}