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

void test_reverse() {
    std::vector<int> v_ints {10, 30, 50, 20, 40};
    LOG(INFO) << "Before Reverse: ";

    std::for_each(v_ints.begin(), v_ints.end(), print_ele<int>());

    std::reverse(v_ints.begin(), v_ints.end());

    LOG(INFO) << "After Reverse: ";

    std::for_each(v_ints.begin(), v_ints.end(), print_ele<int>());
}

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    test_reverse();
    return EXIT_SUCCESS;
}