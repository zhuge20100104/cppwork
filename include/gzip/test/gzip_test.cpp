#include "gzip/gzip_reader.h"
#include <pystring/pystring.h>

#include <gtest/gtest.h>

#include <vector>

GTEST_TEST(GReaderTests, ReadFileToStream) {
    auto res = gzip_reader::read_file("../../../http/test/build/data.10000001.20191031.3.csv.gz");
    std::vector<std::string> results;
    pystring::split(res, results, "\n");
    ASSERT_TRUE(results[0] != "");
}