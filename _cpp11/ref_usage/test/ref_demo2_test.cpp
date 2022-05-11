#include "ref_demo2/ref_demo2.h"

#include <gtest/gtest.h>


GTEST_TEST(RefDemo2Tests, Add){
    int a = 3;
    int b = 2;
    int result {0};
    add(a, b, result);
    ASSERT_EQ(5, result);
}

GTEST_TEST(RefDemo2Tests, Factorial) {
    int a = 5;
    int result {1};
    factorial(a, result);
    ASSERT_EQ(120, result);
}

GTEST_TEST(RefDemo2Tests, Swap) {
    int a = 4;
    int b = 5;
    swap(a, b);
    ASSERT_EQ(5, a);
    ASSERT_EQ(4, b);
}