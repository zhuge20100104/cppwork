#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "intepreter_lex.hpp"
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

GTEST_TEST(CommandTests, Command) {
    std::string input {"(13-4)-(12+1)"};
    auto tokens = lex(input);
    for(auto&& t: tokens) {
        std::cout << t << " ";
    }
    std::cout << "\n";
}