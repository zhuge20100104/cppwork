
#include "journal.h"
#include "persis_manager.h"

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

GTEST_TEST(SingleRespTests, SingleResp) {
    Journal j {"Dear Diary"};
    j.add_entry("I ate a bug");
    j.add_entry("I cried today");
    
    PersisManager::save(j, "diary.txt");
}