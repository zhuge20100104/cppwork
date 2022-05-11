#include "death_handler/death_handler.h"
#include <glog/logging.h>

#include "point_fact.hpp"

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

GTEST_TEST(FactoryTests, Factory) {
    auto pt = PointFactory::NewPolar(5.0f, M_PI_4);
    std::cout << pt << std::endl;
}