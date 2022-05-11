#include "glog/logging.h"

inline int const& max(int const& a, int const& b) {
    return a < b? b: a;
}

template <typename T>
inline T const& max(T const& a, T const& b) {
    return a < b? b: a;
}

template <typename T>
inline T const& max(T const& a, T const& b, T const& c) {
    return ::max(::max(a, b), c);
}

int main(int argc, char* argv[]) {
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");
    LOG(INFO) << ::max(7, 42, 68) << "\n";   // calls the template for three arguments
    LOG(INFO) << ::max(7.0, 42.0) << "\n";   // calls max<double> (by argument deduction)
    LOG(INFO) << ::max('a', 'b') << "\n";    // calls max<char> (by argument deduction)
    LOG(INFO) << ::max(7, 42) << "\n";       // calls the nontemplate for two ints
    LOG(INFO) << ::max<>(7,42) << "\n";      // calls max<int> (by argument deduction)   
    LOG(INFO) << ::max<double>(7, 42) << "\n"; // calls max<double> (no argument deduction)
    LOG(INFO) << ::max('a', 42.7) << "\n";   // calls the nontemplate for two ints
    return 0;
}