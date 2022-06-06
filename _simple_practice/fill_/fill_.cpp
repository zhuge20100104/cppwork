#include <algorithm>
#include <numeric>
#include <functional>
#include <vector>

#include "death_handler/death_handler.h"
#include "glog/logging.h"

template <typename T>
struct print_ele {
    void operator()(T const& i) { LOG(INFO) << i; }
};

void test_fill() {
    std::vector<int> v;
    v.resize(10);

    std::fill(v.begin(), v.end(), 100);
    LOG(INFO) << "After fill: ";
    std::for_each(v.begin(), v.end(), print_ele<int>());
}

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;

    google::InitGoogleLogging("./logs.log");

    test_fill();
    return EXIT_SUCCESS;
}