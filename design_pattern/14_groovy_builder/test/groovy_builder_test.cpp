#include "death_handler/death_handler.h"
#include "json/json.hpp"
#include <glog/logging.h>
#include "groovy_builder.hpp"
#include <gtest/gtest.h>
#include "df/df.h"

using json = nlohmann::json;
using namespace html;

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
    std::cout << P {
        IMG {
            "https://img0.baidu.com/it/u=888809336,3658067701&fm=253&fmt=auto&app=138&f=JPEG?w=500&h=699"
        }
    } << std::endl;
}