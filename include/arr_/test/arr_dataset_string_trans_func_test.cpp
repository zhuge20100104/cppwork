#include "arr_/arr_.h"
#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include <gtest/gtest.h>


#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;

    Debug::DeathHandler dh;

    google::InitGoogleLogging("./logs.log");
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}


auto SRC_SCHEMA = ::arrow::schema(
    {{arrow::field("a", arrow::utf8())}});

auto DST_SCHEMA = ::arrow::schema({{arrow::field("a", arrow::utf8())},
                                   {arrow::field("res", arrow::utf8())}});

auto DST_LEN_SCHEMA = ::arrow::schema({{arrow::field("a", arrow::utf8())},
                                   {arrow::field("res", arrow::int32())}});

std::string const TO_LOWER_TABLE =  R"([
                                            {"a": "Hello World"},
                                            {"a": "Zhangsan"},
                                            {"a": "F4"},
                                            {"a": "Lisi"},
                                            {"a": "Wangwu"}
                                            ])";

std::string const TO_LOWER_RES_TABLE =  R"([
                                            {"a": "Hello World", "res": "hello world"},
                                            {"a": "Zhangsan", "res": "zhangsan"},
                                            {"a": "F4", "res": "f4"},
                                            {"a": "Lisi", "res": "lisi"},
                                            {"a": "Wangwu", "res": "wangwu"}
                                            ])";

std::string const REVERSE_RES_TABLE =  R"([
                                            {"a": "Hello World", "res": "dlroW olleH"},
                                            {"a": "Zhangsan", "res": "nasgnahZ"},
                                            {"a": "F4", "res": "4F"},
                                            {"a": "Lisi", "res": "isiL"},
                                            {"a": "Wangwu", "res": "uwgnaW"}
                                            ])";

std::string const TO_UPPER_RES_TABLE =  R"([
                                            {"a": "Hello World", "res": "HELLO WORLD"},
                                            {"a": "Zhangsan", "res": "ZHANGSAN"},
                                            {"a": "F4", "res": "F4"},
                                            {"a": "Lisi", "res": "LISI"},
                                            {"a": "Wangwu", "res": "WANGWU"}
                                            ])";

std::string const BLEN_RES_TABLE =  R"([
                                            {"a": "Hello World", "res": 11},
                                            {"a": "Zhangsan", "res": 8},
                                            {"a": "F4", "res": 2},
                                            {"a": "Lisi", "res": 4},
                                            {"a": "Wangwu", "res": 6}
                                            ])";

std::string const REPLACE_SUBSTR_RES_TABLE =  R"([
                                            {"a": "Hello World", "res": "Hello World"},
                                            {"a": "Zhangsan", "res": "ZhC++san"},
                                            {"a": "F4", "res": "F4"},
                                            {"a": "Lisi", "res": "Lisi"},
                                            {"a": "Wangwu", "res": "WC++wu"}
                                            ])";

std::string const REPLACE_SUBSTR_REGEX_RES_TABLE =  R"([
                                            {"a": "Hello World", "res": "Hello World"},
                                            {"a": "Zhangsan", "res": "C++"},
                                            {"a": "F4", "res": "F4"},
                                            {"a": "Lisi", "res": "Lisi"},
                                            {"a": "Wangwu", "res": "C++"}
                                            ])";

GTEST_TEST(DatasetStringTransTests, StrTransLower) {
    // 转换字符串到小写
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {TO_LOWER_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_lower", {arrow::compute::field_ref("a")})},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {TO_LOWER_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   


GTEST_TEST(DatasetStringTransTests, StrTransReverse) {
    // 字符串倒序
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {TO_LOWER_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_reverse", {arrow::compute::field_ref("a")})},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {REVERSE_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   


GTEST_TEST(DatasetStringTransTests, StrTransUpper) {
    // 字符串转大写
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {TO_LOWER_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_upper", {arrow::compute::field_ref("a")})},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {TO_UPPER_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
} 


GTEST_TEST(DatasetStringTransTests, BinaryLength) {
    // 查看字符串的二进制长度
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {TO_LOWER_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("binary_length", {arrow::compute::field_ref("a")})},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_LEN_SCHEMA, {BLEN_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
} 

GTEST_TEST(DatasetStringTransTests, ReplaceSubstring) {
    // 替换子字符串
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {TO_LOWER_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    arrow::compute::ReplaceSubstringOptions options{"ang", "C++"};

    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("replace_substring", {arrow::compute::field_ref("a")}, options)},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {REPLACE_SUBSTR_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
} 

GTEST_TEST(DatasetStringTransTests, ReplaceSubstringRegex) {
    // 正则替换子字符串
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {TO_LOWER_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    arrow::compute::ReplaceSubstringOptions options{".*ang.*", "C++"};

    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("replace_substring_regex", {arrow::compute::field_ref("a")}, options)},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {REPLACE_SUBSTR_REGEX_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
} 

