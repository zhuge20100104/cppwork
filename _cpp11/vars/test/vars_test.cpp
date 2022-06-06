#include "vars/vars.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

GTEST_TEST(VarsTests, DefVars) {
    Vars vars {def_vars()};
    ASSERT_EQ(0, vars.i);
    ASSERT_EQ('a', vars.ch);
    ASSERT_EQ(true, vars.flag);
    ASSERT_EQ(1.283f, vars.f);
    ASSERT_EQ(521.342, vars.d);
    ASSERT_THAT(vars.arr, testing::ElementsAre(1, 2, 3, 4, 5));
}