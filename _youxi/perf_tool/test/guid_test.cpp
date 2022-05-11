#include "utils/guid_gen.h"

#include <gtest/gtest.h>

GTEST_TEST(GuidTests, GenUUIDStr) {
    auto uuid_str = GUIDGen::gen_uuid_str();
    std::cerr << uuid_str << std::endl;
    ASSERT_NE("", uuid_str);
}