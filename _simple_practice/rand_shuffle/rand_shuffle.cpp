#include "glog/logging.h"
#include "death_handler/death_handler.h"

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>

void test_rand_shuffle() {
    std::vector<int> v_ints;
    for(int&& i=0; i<10; ++i) {
        v_ints.emplace_back(i);
    }
    
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(v_ints.begin(), v_ints.end(), std::default_random_engine(seed));

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

    test_rand_shuffle();
    return EXIT_SUCCESS;
}