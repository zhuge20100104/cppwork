#include "uniform_init/uniform_init.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>


GTEST_TEST(UniformInitTests, Init) {
    auto initializer = init();
    ASSERT_EQ(0, initializer.a1);
    ASSERT_EQ(0, initializer.a2);
    ASSERT_EQ(5, initializer.a3);
    ASSERT_EQ("", initializer.s1);
    ASSERT_EQ("C++", initializer.s2);
    
    ASSERT_THAT(initializer.d1, testing::ElementsAre('\0','\0','\0','\0', '\0', '\0','\0','\0'));

    ASSERT_THAT(initializer.d2, testing::ElementsAre('\0','\0','\0','\0', '\0', '\0','\0','\0'));

    ASSERT_THAT(initializer.d3, testing::ElementsAre('a','b','c','d', '\0', '\0','\0','\0'));

    ASSERT_THAT(initializer.d4, testing::ElementsAre('a','b','c','d', '\0', '\0','\0','\0'));

    ASSERT_EQ(0, *(initializer.p1));

    ASSERT_EQ("Hello", std::string(initializer.p2.get()));

    ASSERT_EQ(20.0f, initializer.f);
}   
