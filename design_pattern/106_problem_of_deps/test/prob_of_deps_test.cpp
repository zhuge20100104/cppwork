#include "prob_of_deps.hpp"

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

// Code for problem of deps
GTEST_TEST(ProbOfDepsTests, ProbOfDeps) {
    Person p{14};

    p.set_age(15);
    p.set_age(16);
}   