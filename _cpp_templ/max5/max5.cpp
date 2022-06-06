#include <string>
#include <cstring>

#include "glog/logging.h"
#include "death_handler/death_handler.h"

template <typename T>
inline T const& max(T const& a, T const& b) {
    LOG(INFO) << "T const" << "\n";
    return a < b? b: a;
}

template<>
inline char const* const& max<char const*>(char const* const& a, char const* const& b) {
    LOG(INFO) << "char const*" << "\n";
    return std::strcmp(a, b) < 0 ? b: a;
}


int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;

    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    std::string s;

    LOG(INFO) << ::max<char const*>("apple", "peach") << "\n";
    LOG(INFO) << ::max<char const*>("apple", "tomato") << "\n";
    LOG(INFO) << ::max<char const*>("apple", s.c_str()) << "\n";
}