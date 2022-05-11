#include "check_api/check_api.h"

#include <gtest/gtest.h>

const std::vector<std::string> countries {"BH", "EC", "GT", "KG", "LK",
                 "MD", "RS", "TT", "AM", "DZ", "BA", "GH", "BO", "BY", "LU", 
                 "DO", "HN", "KH", "IQ", "JM", "JO", "MO", "SI", "UZ", "MK",
                 "NP", "MA", "PY", "SV", "OM", "PA", "TZ", "QA", "TN", "UY", 
                 "VE", "YE"};

GTEST_TEST(CheckApiTests, CheckTopApps) {
    auto res = check_top_apps(countries);
    ASSERT_TRUE(res);
}


GTEST_TEST(CheckApiTests, CheckAppRankHistory) {
    auto res = check_v12_app_rank_history(countries);
    ASSERT_TRUE(res);
}

GTEST_TEST(CheckApiTests, CheckTopPublishers) {
    auto res = check_top_publisher(countries);
    ASSERT_TRUE(res);
}


GTEST_TEST(CheckApiTests, CheckPublisherHistory) {
    auto res = check_publisher_history(countries);
    ASSERT_TRUE(res);
}

GTEST_TEST(CheckApiTests, CheckTopAppsMobile) {
    auto res = check_top_apps_mobile(countries);
    ASSERT_TRUE(res);
}

GTEST_TEST(CheckApiTests, CheckTopPublisherMobile) {
    auto res = check_top_publisher_mobile(countries);
    ASSERT_TRUE(res);
}

GTEST_TEST(CheckApiTests, CheckAppRankHistoryMobile) {
    auto res = check_app_rank_history_mobile(countries);
    ASSERT_TRUE(res);
}

GTEST_TEST(CheckApiTests, CheckPublisherHistoryMobile) {
    auto res = check_publisher_history_mobile(countries);
    ASSERT_TRUE(res);
}


