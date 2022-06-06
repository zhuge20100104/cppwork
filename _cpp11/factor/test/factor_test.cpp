#include "factor/factor.h"

#include <gtest/gtest.h>


GTEST_TEST(FactorTests, Factorial) {
    ASSERT_EQ(120, factorial(5));
}