#include "pointers/pointers.h"

#include <gtest/gtest.h>

GTEST_TEST(PointersTests, CreatePointer) {
    auto pointer = create_pointer(10);
    ASSERT_EQ(typeid(int*), typeid(pointer.get()));
    ASSERT_EQ(10, *pointer);
}