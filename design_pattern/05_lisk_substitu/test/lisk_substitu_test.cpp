#include "rectangle.hpp"

#include "death_handler/death_handler.h"
#include "json/json.hpp"
#include <glog/logging.h>

#include <gtest/gtest.h>
#include "df/df.h"

using json = nlohmann::json;

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

GTEST_TEST(LiskSubstituTests, LiskSubstitu) {
    auto rect = Rect::Factory::create_rect(3, 4);
    // width: 3 height: 10 -> 30
    process(rect);
    // width: 5 height: 10 -> 50
    auto square = Rect::Factory::create_square(5);
    process(square);
}