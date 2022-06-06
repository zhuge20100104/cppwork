#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "dyna_decorator.hpp"

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

GTEST_TEST(DynaDecoratorTests, DynaDecorator) {
    Square square {5};
    ColoredShape red_square {square, "red"};
    std::cout << square.str() << std::endl << red_square.str() << std::endl;

    TransparentShape trans_square {red_square, 51};
    std::cout << trans_square.str() << std::endl;
}