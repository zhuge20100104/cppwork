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

void test_swap() {
    std::vector<int> v1;
    std::vector<int> v2;
    v1.resize(10);
    v2.resize(10);
    auto i = 0;
    for(int i=0; i<10; ++i) {
        v1[i] = i;
        v2[i] = 100 +i;
    }

    LOG(INFO) << "交换前: ";
    std::for_each(v1.begin(), v1.end(), print_ele<int>());
    std::for_each(v2.begin(), v2.end(), print_ele<int>());

    std::swap(v1, v2);
    LOG(INFO) << "交换后: ";
    std::for_each(v1.begin(), v1.end(), print_ele<int>());
    std::for_each(v2.begin(), v2.end(), print_ele<int>());
}

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    test_swap();
    return EXIT_SUCCESS;
}