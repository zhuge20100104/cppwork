#include "hello_world/hello_world.h"

#include <gtest/gtest.h>

#include <string>

GTEST_TEST(HelloWorldTests, SayHello) {
    testing::internal::CaptureStdout();
    say_hello();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("Hello C++\n", output);
}