#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "property_proxy.hpp"

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

GTEST_TEST(PropertyProxyTests, PropertyProxy) {
    Creature c; 
    c.strength = 11;
    int x = c.agility;
    std::cout << "c.strength = " << c.strength << "\n";
    std::cout << "c.agility = " << x << "\n";
}