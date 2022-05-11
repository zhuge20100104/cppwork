
#include <gtest/gtest.h>

#include "cal/cal.h"

GTEST_TEST(CalSuite, AddTest) {
    ASSERT_EQ(5, add(3,2));
}

GTEST_TEST(CalSuite, SubTest) {
    ASSERT_EQ(1, sub(3, 2));
}