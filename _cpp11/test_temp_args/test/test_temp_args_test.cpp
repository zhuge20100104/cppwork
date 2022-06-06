#include "test_temp_args/test_temp_args.h"

#include <gtest/gtest.h>

#include <string>

GTEST_TEST(TestTempArgsTests, BindParams) {
    bind_params("select * from test limit 1", 1, "222", 3.5, 200000000000000055);
}