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

void test_accumulate() {
    std::vector<int> v;
    for (int i = 1; i <= 100; ++i) {
        v.emplace_back(std::move(i));
    }

    auto res = std::accumulate(v.begin(), v.end(), 0);
    LOG(INFO) << "Accumulate of (1 to 100): " << res;
}

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;

    google::InitGoogleLogging("./logs.log");

    test_accumulate();
    return EXIT_SUCCESS;
}