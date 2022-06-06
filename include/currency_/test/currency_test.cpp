#include "currency_/currency_.h"
#include <gtest/gtest.h>

#include <string>


GTEST_TEST(CurrencyTests, CheckCurrency) {
    bool check_res = currency_util::check_currencies();
    ASSERT_TRUE(check_res);
}