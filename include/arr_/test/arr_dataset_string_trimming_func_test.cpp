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

std::string const TRIM_TABLE =  R"([
                                            {"a": "  hello"},
                                            {"a": "  world  "},
                                            {"a": "Zhangsan  "},
                                            {"a": "  Zhangsan   "}
                                            ])";

std::string const TRIM_LEFT_RES_TABLE =  R"([
                                            {"a": "  hello", "res": "hello"},
                                            {"a": "  world  ", "res": "world  "},
                                            {"a": "Zhangsan  ", "res": "Zhangsan  "},
                                            {"a": "  Zhangsan   ", "res": "Zhangsan   "}
                                            ])";

std::string const TRIM_RIGHT_RES_TABLE =  R"([
                                            {"a": "  hello", "res": "  hello"},
                                            {"a": "  world  ", "res": "  world"},
                                            {"a": "Zhangsan  ", "res": "Zhangsan"},
                                            {"a": "  Zhangsan   ", "res": "  Zhangsan"}
                                            ])";


std::string const TRIM_ALL_RES_TABLE =  R"([
                                            {"a": "  hello", "res": "hello"},
                                            {"a": "  world  ", "res": "world"},
                                            {"a": "Zhangsan  ", "res": "Zhangsan"},
                                            {"a": "  Zhangsan   ", "res": "Zhangsan"}
                                            ])";

GTEST_TEST(DatasetStringTrimmingTests, StrTrimLeft) {
    // 去除左边空格
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {TRIM_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    arrow::compute::TrimOptions options {" "};
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_ltrim", {arrow::compute::field_ref("a")}, options)},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {TRIM_LEFT_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   


GTEST_TEST(DatasetStringTrimmingTests, StrTrimLeftWhiteSpace) {
    // 去除左边空格
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {TRIM_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_ltrim_whitespace", {arrow::compute::field_ref("a")})},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {TRIM_LEFT_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   


GTEST_TEST(DatasetStringTrimmingTests, StrTrimRight) {
    // 去除右边空格
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {TRIM_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    arrow::compute::TrimOptions options {" "};
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_rtrim", {arrow::compute::field_ref("a")}, options)},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {TRIM_RIGHT_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   


GTEST_TEST(DatasetStringTrimmingTests, StrTrimRightWhitespace) {
    // 去除右边空格
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {TRIM_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    arrow::compute::TrimOptions options {" "};
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_rtrim_whitespace", {arrow::compute::field_ref("a")}, options)},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {TRIM_RIGHT_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   


GTEST_TEST(DatasetStringTrimmingTests, StrTrimAll) {
    // 去除左右空格
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {TRIM_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    arrow::compute::TrimOptions options {" "};
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_trim", {arrow::compute::field_ref("a")}, options)},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {TRIM_ALL_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}

GTEST_TEST(DatasetStringTrimmingTests, StrTrimAllWhitespace) {
    // 去除左右空格
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {TRIM_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    arrow::compute::TrimOptions options {" "};
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_trim_whitespace", {arrow::compute::field_ref("a")}, options)},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {TRIM_ALL_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}