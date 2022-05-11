#include "glog/logging.h"
#include "death_handler/death_handler.h"

#include <cstring>
#include <string>


// 通过值调用
inline char const*&  max(char const*& a, char const*&  b) {
    return std::strcmp(a, b) < 0 ? b : a;
}

// 通过引用调用
template <typename T>
inline T const& max(T const& a, T const& b) {
    return a < b ? b : a;
}

template <typename T>
inline T const& max(T const& a, T const& b, T const& c) {
    // 值函数调用完毕，这个值是个右值，就没有了，会segmentation fault
    return ::max(::max(a, b), c);  // 调用值函数会出错
}

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;

    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    LOG(INFO) << ::max(7, 42, 68) << "\n";
    char const* s1 = "frederic";
    char const* s2 = "anica";
    char const* s3 = "lucas";
    LOG(INFO) << ::max(s1, s2, s3) << "\n";
    return 0;
}