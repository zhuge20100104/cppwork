#include "locale_/test_config.h"
#include "locale_/locale_.h"

#include "death_handler/death_handler.h"
#include <glog/logging.h>

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

GTEST_TEST(LocaleTests, IosLocaleTest) {
    bool ios_compare_res = get_and_compare_ios_countries(ios_locales);
    ASSERT_TRUE(ios_compare_res);
}

GTEST_TEST(LocaleTests, IosTimelineLocaleTest) {
    bool ios_compare_res = get_and_compare_ios_countries_timeline(ios_locales);
    ASSERT_TRUE(ios_compare_res);
}

GTEST_TEST(LocaleTests, GPLocaleTest) {
    bool gp_compare_res = get_and_compare_gp_countries(gp_locales);
    ASSERT_TRUE(gp_compare_res);
}


GTEST_TEST(LocaleTests, GPTimelineLocaleTest) {
    bool gp_compare_res = get_and_compare_gp_countries_timeline(gp_locales);
    ASSERT_TRUE(gp_compare_res);
}

