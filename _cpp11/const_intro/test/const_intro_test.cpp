#include "const_intro/const_intro.h"

#include <gtest/gtest.h>

#include <sstream>
#include <iomanip>


GTEST_TEST(ConstIntroTests, Area) {
    using namespace ConstIntro;
    double radius = 2.0;
    double area_ = area(radius);

    // 解决浮点数精度问题
    std::stringstream ss;
    ss << std::setprecision(9) << area_;
    ASSERT_EQ("12.5663704", ss.str());
}

GTEST_TEST(ConstIntroTests, Circumference) {
    using namespace ConstIntro;
    double radius = 3.0;
    double circum_ = circumference(radius);

    // 解决浮点数精度问题
    std::stringstream ss;
    ss << std::setprecision(9) <<  circum_;
    ASSERT_EQ("18.8495556", ss.str());
}