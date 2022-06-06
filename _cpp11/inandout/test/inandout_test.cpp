#include "inandout/inandout.h"

#include <gtest/gtest.h>

GTEST_TEST(InOutTests, PureOut) {
    testing::internal::CaptureStdout();
    pure_out();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("Hello World\n", output);
}

GTEST_TEST(InOutTests, InAndOutAge) {
    std::ifstream is {"../age.txt"};
    int age {in_and_out_age(is)};
    ASSERT_EQ(23, age);
    ASSERT_TRUE(age < 200); 
}

GTEST_TEST(InOutTests, InAndOutName) {
    std::ifstream is {"../name.txt"};
    std::string name {in_and_out_name(is)};
    ASSERT_EQ("ZhangSan", name);
}