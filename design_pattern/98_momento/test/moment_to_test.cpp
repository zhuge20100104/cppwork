#include "moment_to.hpp"

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <fstream>
#include <memory>
#include <algorithm>

#include "death_handler/death_handler.h"

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

// Moment to 备忘录模式极简实现
GTEST_TEST(EventBrokerTests, EventBroker) {
    BankAccount ba {100};
    auto m1 = ba.deposit(50); // 150
    auto m2 = ba.deposit(25); // 175

    std::cout << ba << "\n";
    ba.restore(m1);
    std::cout << "Back to m1: " << ba << "\n";

    ba.restore(m2);
    std::cout << "Back to m2: " << ba << "\n";
}