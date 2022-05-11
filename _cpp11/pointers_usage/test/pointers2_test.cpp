#include "pointers2/pointers2.h"

#include <gtest/gtest.h>

GTEST_TEST(Pointer2Tests, Add) {
    int a = 1;
    int b = 2;
    int res = add(&a, &b);
    ASSERT_EQ(3, res);
}

GTEST_TEST(Pointer2Tests, AddVal) {
    int a = 2;
    int b = 3;
    int result {0};
    add_val(&a, &b, &result);
    ASSERT_EQ(5, result);
}

GTEST_TEST(Pointer2Tests, Swap) {
    int a = 7;
    int b = 5;
    swap(&a, &b);
    ASSERT_EQ(5, a);
    ASSERT_EQ(7, b);
}

GTEST_TEST(Pointer2Tests, Factorial) {
    int a = 5;
    int result {1};
    factorial(&a, &result);
    ASSERT_EQ(120, result);
}