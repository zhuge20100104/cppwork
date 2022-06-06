#include "ref_demo/ref_demo.h"

#include <gtest/gtest.h>

GTEST_TEST(RefDemoTests, AssignRef) {
    RefDemo rf {};
    assign_ref(rf);
    ASSERT_EQ(20, rf.val);
    ASSERT_EQ(20, rf.x);
}