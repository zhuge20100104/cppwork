#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "printer.hpp"

#include <utility>
#include <gtest/gtest.h>
#include "df/df.h"



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

GTEST_TEST(MonoStateTests, MonoState) {
    Printer p;
    int id = p.get_id();

    Printer p2;
    int id2 = p2.get_id();

    std::cout << id << "\n";
    std::cout << id2 << "\n";
}