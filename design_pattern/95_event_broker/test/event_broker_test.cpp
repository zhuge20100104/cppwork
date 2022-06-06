#include "soccer.hpp"

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <fstream>
#include <memory>
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

// 使用boost::signals2 库实现 教练向所有队员说话
// 其中game是中介者，被所有player持有，负责向所有player发消息
GTEST_TEST(EventBrokerTests, EventBroker) {
    Game game;
    Player player {"sam", game};
    Coach coach {game};

    player.score();
    player.score();
    player.score();
    player.score();
}
