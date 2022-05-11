#include "glog/logging.h"
#include "death_handler/death_handler.h"

#include <vector>
#include <algorithm>

void test_internal_type() {
    std::vector<int> v_ints {
        10, 40, 30, 20, 40, 20
    };

    int num = std::count_if(v_ints.begin(), v_ints.end(), [] (const auto& ele) {
        return ele > 20;
    });
    LOG(INFO) << "大于20的元素个数为: " << num;
}

struct person {
    std::string name;
    int age;
};

void test_custom_type() {
    std::vector<person> v_person {
        {"刘备", 35},
        {"关羽", 35},
        {"张飞", 35},
        {"赵云", 40},
        {"曹操", 20}
    };

    int num = std::count_if(v_person.begin(), v_person.end(), [](const auto& person_) {
        return person_.age > 20;
    });

    LOG(INFO) << "年龄大于20的人数为: " << num;
}

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    test_internal_type();
    test_custom_type();
    return EXIT_SUCCESS;
}