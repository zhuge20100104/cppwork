#include "func1/func1.h"

#include <gtest/gtest.h>

GTEST_TEST(Func1Tests, Add) {
    int x = 3;
    int y = 4;
    ASSERT_EQ(7, add(x, y));
}