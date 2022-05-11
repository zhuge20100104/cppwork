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

void test_merge() {
    std::vector<int> v1;
    std::vector<int> v2;

    // Merge区间内元素必须是有序的，所以需要用 std::sort先排序
    for(int i=0; i<10; ++i) {
        v1.emplace_back(i);
        v2.emplace_back(i+1);
    }

    std::vector<int> v_target;
    v_target.resize(v1.size() + v2.size());

    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v_target.begin());

    std::for_each(v_target.begin(), v_target.end(), print_ele<int>());

    LOG(INFO) << "\n";
}

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    test_merge();
    return EXIT_SUCCESS;
}