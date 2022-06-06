#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "array_be_prop.hpp"

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

GTEST_TEST(ArrayBEPropTests, ArrayBEProp) {
    Creature c;
    c.set_strength(16);
    c.set_agility(11);
    c.set_intelligence(9);

    std::cout << "The orc has an average stat of "
        << c.average()
        << " and a maximum stat of "
        << c.max()
        << "\n";
}