#include "glog/logging.h"
#include "death_handler/death_handler.h"

#include <vector>
#include <algorithm>
#include <functional>


template <typename T>
struct print_ele {
    void operator()(T const& i) {
        LOG(INFO) << i;
    }
}; 


void test_copy() {
    std::vector<int> v1;
    v1.resize(10);
    int i = 0;
    // 1, 2, 3, 4 ... 10
    std::for_each(v1.begin(), v1.end(), [&i](auto& ele) {
        ele = ++i; 
    });

    std::vector<int> v2;
    v2.resize(v1.size());
    std::copy(v1.begin(), v1.end(), v2.begin());
    LOG(INFO) << "After Copy ...";
    std::for_each(v2.begin(), v2.end(), print_ele<int>());
}

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    test_copy();
    return EXIT_SUCCESS;
}