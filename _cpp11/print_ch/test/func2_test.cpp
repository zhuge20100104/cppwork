#include "func2/func2.h"

#include <gtest/gtest.h>

GTEST_TEST(Func2Tests, Print) {
    testing::internal::CaptureStdout();
    print('#', 10);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("##########\n", output);
}