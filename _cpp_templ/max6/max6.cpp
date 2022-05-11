#include "glog/logging.h"
#include "death_handler/death_handler.h"

#include <string>
#include <cstring>

template <typename T>
inline T max(T a, T b) {
    LOG(INFO) << "max<T>";
    return a < b ? b: a;
}

template <>
inline char const* max<char const*>(char const* a, char const* b) {
    LOG(INFO) << "max<char const*>";
    return std::strcmp(a, b) < 0 ? b : a;
}

// TODO: Add const char* overload

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;

    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    std::string s;

    LOG(INFO) << ::max("apple", "peach") << "\n";
    LOG(INFO) << ::max("apple", "tomato") << "\n";
    LOG(INFO) << ::max("apple", s.c_str()) << "\n";
    return 0;
}