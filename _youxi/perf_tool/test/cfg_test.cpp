#include "utils/cfg_reader.h"

#include <gtest/gtest.h>

GTEST_TEST(CfgTests, CfgReaderTest) {
    std::map<std::string, std::string> cfg_;
    auto res = cfg_reader::read_file("../../conf/master.conf", cfg_);
    ASSERT_TRUE(res);
    ASSERT_EQ(6, cfg_.size());
}
