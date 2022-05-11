#include "const_intro2/const_intro2.h"

#include <gtest/gtest.h>

GTEST_TEST(ConstIntro2Tests, PrintPtr) {
    int x = 10;
    testing::internal::CaptureStdout();
    print(&x);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("10\n", output);
}

GTEST_TEST(ConstIntro2Tests, PrintRef) {
    int x = 20;
    testing::internal::CaptureStdout();
    print(x);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("20\n", output);
}

GTEST_TEST(ConstIntro2Tests, GetConstEle) {
    const std::shared_ptr<int> ele = get_const_ele();
    ASSERT_EQ(512, *ele);
}