#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "multiton.hpp"

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

GTEST_TEST(MultitonTests, Multiton) {
    auto main = MultitonPrinter::get(Importance::Primary);
    auto aux = MultitonPrinter::get(Importance::Secondary);
    auto aux2 = MultitonPrinter::get(Importance::Secondary);

    auto small = MultitonCircle::get(Size::Small);
    auto medium = MultitonCircle::get(Size::Medium, 2.0f);
    auto large = MultitonCircle::get(Size::Large, 3.0f);
}