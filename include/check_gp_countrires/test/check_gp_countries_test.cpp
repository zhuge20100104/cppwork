#include "check_gp_countrires/test_config.h"
#include "check_gp_countrires/check_gp_countries.h"
#include <gtest/gtest.h>


bool run_a_test_case(const std::string& case_name) {
    std::cout << "Test Case: [" << case_name << "] Started !" << std::endl;
    auto test_case = TestEles[case_name];
    auto res = send_request_query(test_case);
    std::cout << "Test Case: [" << case_name << "] End !" << std::endl;
    return res;
}

GTEST_TEST(CheckGPCountriesTests, StoreProductRankPaidCase) {
    bool test_result = run_a_test_case(StoreProductRankPaidCase);
    ASSERT_EQ(true, test_result);
}

GTEST_TEST(CheckGPCountriesTests, TopCompanyOverviewTableCase) {
    bool test_result = run_a_test_case(TopCompanyOverviewTableCase);
    ASSERT_EQ(true, test_result);
}

GTEST_TEST(CheckGPCountriesTests, DownloadChannelTableCase) {
    bool test_result = run_a_test_case(DownloadChannelTableCase);
    ASSERT_EQ(true, test_result);
}