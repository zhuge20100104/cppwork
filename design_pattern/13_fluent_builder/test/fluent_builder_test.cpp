#include "death_handler/death_handler.h"
#include "json/json.hpp"
#include <glog/logging.h>
#include "fluent_builder.hpp"
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

GTEST_TEST(BuilderTests, Builder) {
    HTMLElement ele = HTMLBuilder::create("ul")
        .add_child("li", "hello")
        .add_child("li", "word");
    std::cout << ele.str() << std::endl;
}