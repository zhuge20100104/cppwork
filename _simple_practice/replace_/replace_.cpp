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

void test_replace() {
    std::vector<int> v_ints {20, 30, 50, 30, 40, 20, 10, 20};
    LOG(INFO) << "Before Replace: ";
    std::for_each(v_ints.begin(), v_ints.end(), print_ele<int>());
    
    std::replace(v_ints.begin(), v_ints.end(), 20, 2000);
    LOG(INFO) << "After Replace: ";
    std::for_each(v_ints.begin(), v_ints.end(), print_ele<int>());
}

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    test_replace();
    return EXIT_SUCCESS;
}