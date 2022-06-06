#include "moment_to_undo.hpp"

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

// Moment to 备忘录模式支持undo和redo
GTEST_TEST(MomentoTests, Momento) {
    BankAccount ba {100};
    ba.deposit(50); // 150
    ba.deposit(25); // 175

    std::cout << ba << std::endl;
    ba.undo();
    std::cout << "undo 1: " << ba << std::endl;  // 150
    ba.undo();
    std::cout << "undo 2: " << ba << std::endl;  // 100

    ba.redo();
    std::cout << "redo: " << ba << std::endl; //150
}