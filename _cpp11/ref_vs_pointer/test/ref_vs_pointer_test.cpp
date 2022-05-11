#include "ref_vs_pointer/ref_vs_pointer.h"

#include <gtest/gtest.h>

GTEST_TEST(RefVsPointerTests, SwapPointer) {
    int a = 3;
    int b = 2;
    swap(&a, &b);
    ASSERT_EQ(2, a);
    ASSERT_EQ(3, b);
}

GTEST_TEST(RefVsPointerTests, SwapRef) {
    int a = 5;
    int b = 10;
    swap(a, b);
    ASSERT_EQ(10, a);
    ASSERT_EQ(5, b);
}

GTEST_TEST(RefVsPointerTests, PrintPointer) {
    testing::internal::CaptureStdout();
    int a = 10;
    print(nullptr);
    print(&a);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("10\n", output);
}

GTEST_TEST(RefVsPointerTests, PrintRef) {
    testing::internal::CaptureStdout();
    int a = 5;
    print(a);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("5\n", output);
}

