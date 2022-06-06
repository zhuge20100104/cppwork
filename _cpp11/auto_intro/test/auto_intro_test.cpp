#include "auto_intro/auto_intro.h"

#include <gtest/gtest.h>

GTEST_TEST(AutoIntroTests, DefineAutoVar) {
    auto res = define_auto_var();
    ASSERT_EQ(10, *res);
}

GTEST_TEST(AutoIntroTests, FuncReturn) {
    auto ret = sum(7, 4);
    ASSERT_EQ(11, ret);
}

GTEST_TEST(AutoIntroTests, GetList) {
    auto ls = getlist();
    ASSERT_EQ(5, ls.size());
    auto begin = ls.begin();
    
    ASSERT_EQ(1, *begin);
    ASSERT_EQ(2, *(++begin));
    ASSERT_EQ(3, *(++begin));
    ASSERT_EQ(4, *(++begin));
    ASSERT_EQ(5, *(++begin));
}