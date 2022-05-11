#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "singleton_rec_finder.hpp"

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

GTEST_TEST(TestabilityIssueTests, TestabilityIssue) {
    // 这里直接从生产拿数据，不合适。因为生产的数据可能会变，
    // 一旦生产的数据变了，测试用例可能会失败
    SingletonRecordFinder rf;
    std::vector<std::string> cities {"Seoul", "Mexico City"};
    int tp = rf.total_population(cities);
    EXPECT_EQ(17500000 + 17400000, tp);
}