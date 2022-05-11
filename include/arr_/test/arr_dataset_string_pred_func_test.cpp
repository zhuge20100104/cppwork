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
                                   {arrow::field("res", arrow::boolean())}});

std::string const AL_NUM_TABLE =  R"([
                                            {"a": "Hello World"},
                                            {"a": "Zhangsan"},
                                            {"a": "F4"},
                                            {"a": "Lisi"},
                                            {"a": "Wangwu"}
                                            ])";

std::string const AL_NUM_RES_TABLE =  R"([
                                            {"a": "Hello World", "res": false},
                                            {"a": "Zhangsan", "res": true},
                                            {"a": "F4", "res": true},
                                            {"a": "Lisi", "res": true},
                                            {"a": "Wangwu", "res": true}
                                            ])";

std::string const AL_RES_TABLE =  R"([
                                            {"a": "Hello World", "res": false},
                                            {"a": "Zhangsan", "res": true},
                                            {"a": "F4", "res": false},
                                            {"a": "Lisi", "res": true},
                                            {"a": "Wangwu", "res": true}
                                            ])";


std::string const DECIMAL_TABLE =  R"([
                                            {"a": "3"},
                                            {"a": "5"},
                                            {"a": "C++"},
                                            {"a": "Java"},
                                            {"a": "2"}
                                            ])";


std::string const DECIMAL_RES_TABLE =  R"([
                                            {"a": "3", "res": true},
                                            {"a": "5", "res": true},
                                            {"a": "C++", "res": false},
                                            {"a": "Java", "res": false},
                                            {"a": "2", "res": true}
                                            ])";

std::string const IS_LOWER_RES_TABLE =  R"([
                                            {"a": "Hello World", "res": false},
                                            {"a": "Zhangsan", "res": false},
                                            {"a": "F4", "res": false},
                                            {"a": "Lisi", "res": false},
                                            {"a": "Wangwu", "res": false}
                                            ])";

std::string const IS_PRINTABLE_RES_TABLE =  R"([
                                            {"a": "Hello World", "res": true},
                                            {"a": "Zhangsan", "res": true},
                                            {"a": "F4", "res": true},
                                            {"a": "Lisi", "res": true},
                                            {"a": "Wangwu", "res": true}
                                            ])";

std::string const SPACE_TABLE =  R"([
                                            {"a": " "},
                                            {"a": "  "},
                                            {"a": "     "},
                                            {"a": "Hello"},
                                            {"a": "2"}
                                            ])";

std::string const SPACE_RES_TABLE =  R"([
                                            {"a": " ", "res": true},
                                            {"a": "  ", "res": true},
                                            {"a": "     ", "res": true},
                                            {"a": "Hello", "res": false},
                                            {"a": "2", "res": false}
                                            ])";

std::string const IS_UPPER_RES_TABLE =  R"([
                                            {"a": "Hello World", "res": false},
                                            {"a": "Zhangsan", "res": false},
                                            {"a": "F4", "res": true},
                                            {"a": "Lisi", "res": false},
                                            {"a": "Wangwu", "res": false}
                                            ])";

std::string const UTF_TITLE_TABLE =  R"([
                                            {"a": "Zhangsan٣Lunwen"},
                                            {"a": "Lisi٣Lunwen"},
                                            {"a": "Haha٣Hahaha"}
                                            ])";

std::string const UTF_TITLE_RES_TABLE =  R"([
                                            {"a": "Zhangsan٣Lunwen", "res": true},
                                            {"a": "Lisi٣Lunwen", "res": true},
                                            {"a": "Haha٣Hahaha", "res": true}
                                            ])";


std::string const IS_ASCII_RES_TABLE =  R"([
                                            {"a": "Zhangsan٣Lunwen", "res": false},
                                            {"a": "Lisi٣Lunwen", "res": false},
                                            {"a": "Haha٣Hahaha", "res": false}
                                            ])";

GTEST_TEST(DatasetStringPredTests, StrPredIsAlnum) {
    // 是否ASCII 字母和数字
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {AL_NUM_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_is_alnum", {arrow::compute::field_ref("a")})},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {AL_NUM_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   


GTEST_TEST(DatasetStringPredTests, StrPredIsAlpha) {
    // 是否ASCII 字母
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {AL_NUM_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_is_alpha", {arrow::compute::field_ref("a")})},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {AL_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   

GTEST_TEST(DatasetStringPredTests, StrPredIsDecimal) {
    // 是否是浮点数
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {DECIMAL_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_is_decimal", {arrow::compute::field_ref("a")})},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {DECIMAL_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   

GTEST_TEST(DatasetStringPredTests, StrPredIsLower) {
    // 是否是小写字母
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {AL_NUM_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_is_lower", {arrow::compute::field_ref("a")})},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {IS_LOWER_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   

GTEST_TEST(DatasetStringPredTests, StrPredIsPrintable) {
    // 是否可打印字符
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {AL_NUM_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_is_printable", {arrow::compute::field_ref("a")})},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {IS_PRINTABLE_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   


GTEST_TEST(DatasetStringPredTests, StrPredIsSpace) {
    // 是否是空格
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {SPACE_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_is_space", {arrow::compute::field_ref("a")})},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {SPACE_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   


GTEST_TEST(DatasetStringPredTests, StrPredIsUpper) {
    // 是否是大写字母
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {AL_NUM_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_is_upper", {arrow::compute::field_ref("a")})},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {IS_UPPER_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
} 


GTEST_TEST(DatasetStringPredTests, StrPredIsUtf8Alnum) {
    // 是否ASCII 字母和数字
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {AL_NUM_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("utf8_is_alnum", {arrow::compute::field_ref("a")})},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {AL_NUM_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   


GTEST_TEST(DatasetStringPredTests, StrPredIsUtf8Title) {
    // 是否是Utf8 title格式
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {UTF_TITLE_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("utf8_is_title", {arrow::compute::field_ref("a")})},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {UTF_TITLE_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   


GTEST_TEST(DatasetStringPredTests, StrPredIsAscii) {
    // 是否仅有 ASCII字符组成
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {UTF_TITLE_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("string_is_ascii", {arrow::compute::field_ref("a")})},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {IS_ASCII_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   