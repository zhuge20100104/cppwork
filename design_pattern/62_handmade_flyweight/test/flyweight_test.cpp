#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "hmade_flyweight.hpp"

#include <utility>
#include <gtest/gtest.h>



int main(int argc, char** argv) {
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;

    Debug::DeathHandler dh;

    google::InitGoogleLogging("./logs.log");
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

GTEST_TEST(FlyWeightTests, FlyWeight) {
    User user1 {"John", "Smith"};
    User user2 {"Jane", "Smith"};
    std::cout << user1 << std::endl << user2 << std::endl;
}