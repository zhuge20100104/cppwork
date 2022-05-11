#include "death_handler/death_handler.h"
#include <glog/logging.h>

#include "person"

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

GTEST_TEST(BuildFacetsTests, BuildFacets) {
    Person p = Person::create().lives().at("城花璟苑").with_postcode("430000").in("武汉").works().at("Data.AI").as_a("测试开发").earning(3000);
    std::cout << p << std::endl;
}