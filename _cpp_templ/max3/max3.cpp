#include "glog/logging.h"

#include <cstring>
#include <string>

// maximum of two values of any type
template <typename T>
inline T const& max(T const& a, T const& b) {
    return a < b ? b : a;
}

// maximum of two points
template <typename T>
inline T* const& max(T* const& a, T* const& b) {
    return *a < *b ? b : a;
}

// maxium of two c strings
inline char const* const& max(char const* const& a, char const* const& b) {
    return std::strcmp(a, b) < 0 ? b : a;
}

int main(int argc, char* argv[]) {
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    int a = 7;
    int b = 42;
    LOG(INFO) << ::max(a, b) << "\n";

    std::string s = "hey";
    std::string t = "you";
    LOG(INFO) << ::max(s, t) << "\n";

    int* p1 = &b;
    int* p2 = &a;
    LOG(INFO) << ::max(p1, p2) << "\n";

    char const* const s1 = "David";
    char const* const s2 = "Nico";
    LOG(INFO) << ::max(s1, s2) << "\n";
    return 0;
}