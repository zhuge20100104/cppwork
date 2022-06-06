#include "multi_method.hpp"

#include <glog/logging.h>
#include <gtest/gtest.h>

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

GTEST_TEST(MultiMethodTests, MultiMethod) {
    // 宇宙飞船
    Spaceship spaceship;
    // 小行星
    Asteroid asteroid;
    // 行星
    Planet planet;

    collide(planet, spaceship);
    collide(planet, asteroid);
    collide(spaceship, asteroid);
    collide(planet, planet);
}