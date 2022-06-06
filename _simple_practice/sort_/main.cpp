#include "glog/logging.h"
#include "death_handler/death_handler.h"

#include <vector>
#include <algorithm>
#include <functional>


void test_asc() {
    std::vector<int> v_ints {
        10, 30, 50, 20, 40
    };
    std::sort(v_ints.begin(), v_ints.end());
    std::for_each(v_ints.begin(), v_ints.end(), [](const auto& ele) {
        LOG(INFO) << ele;
    });

    LOG(INFO) << "\n";
}

void test_desc() {
    std::vector<int> v_ints {
        10, 30, 50, 20, 40
    };
    std::sort(v_ints.begin(), v_ints.end(), [](const auto& a, const auto& b) {
        return a > b;
    });

    std::for_each(v_ints.begin(), v_ints.end(), [](const auto& ele) {
        LOG(INFO) << ele;
    });
    LOG(INFO) << "\n";
}

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    test_asc();

    test_desc();

    return EXIT_SUCCESS;
}