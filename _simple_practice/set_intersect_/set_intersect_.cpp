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

void test_intersect_() {
    std::vector<int> v1;
    std::vector<int> v2;
    // 用于求交集的两个集合必须是有序的
    for(int i=0; i<10; ++i) {
        v1.emplace_back(i); // 0 -> 9
        v2.emplace_back(i+5); // 5 -> 14
    }
    std::vector<int> v_target;
    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v_target));
    std::for_each(v_target.begin(), v_target.end(), print_ele<int>());
}

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;

    google::InitGoogleLogging("./logs.log");

    test_intersect_();
    return EXIT_SUCCESS;
}