#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "text_formatter.hpp"

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

GTEST_TEST(TextFormatterTests, TextFormatter) {
    FormattedText ft{"This is a brave new world"};
    ft.capitalize(10, 15);
    // 大写brave字符串
    std::cout << ft << std::endl;

    BetterFormattedText bft{"This is a brave new world"};
    bft.get_range(10, 15).capitalize = true;
     // 大写brave字符串
    std::cout << bft << std::endl;
}