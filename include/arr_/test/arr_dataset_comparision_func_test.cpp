#include <glog/logging.h>
#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "arr_/arr_.h"
#include "death_handler/death_handler.h"

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
    {{arrow::field("a", arrow::int32())}, {arrow::field("b", arrow::int32())}});

auto DST_SCHEMA = ::arrow::schema({{arrow::field("a", arrow::int32())},
                                   {arrow::field("b", arrow::int32())},
                                   {arrow::field("res", arrow::boolean())}});

std::string const EQ_TABLE =
    R"([
                                            {"a": 1, "b": 2},
                                            {"a": 2,  "b": 5},
                                            {"a": 3,  "b": 1},
                                            {"a": 4,  "b": 3},
                                            {"a": 5,  "b": 6},
                                            {"a": 6,  "b": 2},
                                            {"a": 7,  "b": 7},
                                            {"a": 8,  "b": 4}
                                            ])";

std::string const EQ_RES_TABLE = R"([
                                            {"a": 1, "b": 2, "res": false},
                                            {"a": 2,  "b": 5, "res": false},
                                            {"a": 3,  "b": 1, "res": false},
                                            {"a": 4,  "b": 3, "res": false},
                                            {"a": 5,  "b": 6, "res": false},
                                            {"a": 6,  "b": 2, "res": false},
                                            {"a": 7,  "b": 7, "res": true},
                                            {"a": 8,  "b": 4, "res": false}
                                            ])";

std::string const NOT_EQ_RES_TABLE = R"([
                                            {"a": 1, "b": 2, "res": true},
                                            {"a": 2,  "b": 5, "res": true},
                                            {"a": 3,  "b": 1, "res": true},
                                            {"a": 4,  "b": 3, "res": true},
                                            {"a": 5,  "b": 6, "res": true},
                                            {"a": 6,  "b": 2, "res": true},
                                            {"a": 7,  "b": 7, "res": false},
                                            {"a": 8,  "b": 4, "res": true}
                                            ])";

std::string const GREATER_RES_TABLE = R"([
                                            {"a": 1, "b": 2, "res": false},
                                            {"a": 2,  "b": 5, "res": false},
                                            {"a": 3,  "b": 1, "res": true},
                                            {"a": 4,  "b": 3, "res": true},
                                            {"a": 5,  "b": 6, "res": false},
                                            {"a": 6,  "b": 2, "res": true},
                                            {"a": 7,  "b": 7, "res": false},
                                            {"a": 8,  "b": 4, "res": true}
                                            ])";


std::string const GREATER_EQ_RES_TABLE = R"([
                                            {"a": 1, "b": 2, "res": false},
                                            {"a": 2,  "b": 5, "res": false},
                                            {"a": 3,  "b": 1, "res": true},
                                            {"a": 4,  "b": 3, "res": true},
                                            {"a": 5,  "b": 6, "res": false},
                                            {"a": 6,  "b": 2, "res": true},
                                            {"a": 7,  "b": 7, "res": true},
                                            {"a": 8,  "b": 4, "res": true}
                                            ])";

std::string const LESS_RES_TABLE = R"([
                                            {"a": 1, "b": 2, "res": true},
                                            {"a": 2,  "b": 5, "res": true},
                                            {"a": 3,  "b": 1, "res": false},
                                            {"a": 4,  "b": 3, "res": false},
                                            {"a": 5,  "b": 6, "res": true},
                                            {"a": 6,  "b": 2, "res": false},
                                            {"a": 7,  "b": 7, "res": false},
                                            {"a": 8,  "b": 4, "res": false}
                                            ])";
std::string const LESS_EQ_RES_TABLE = R"([
                                            {"a": 1, "b": 2, "res": true},
                                            {"a": 2,  "b": 5, "res": true},
                                            {"a": 3,  "b": 1, "res": false},
                                            {"a": 4,  "b": 3, "res": false},
                                            {"a": 5,  "b": 6, "res": true},
                                            {"a": 6,  "b": 2, "res": false},
                                            {"a": 7,  "b": 7, "res": true},
                                            {"a": 8,  "b": 4, "res": false}
                                            ])";


GTEST_TEST(DatasetComparisonTests, ComparisonEqual) {
    // 比较两列是否相等
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {EQ_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"), arrow::compute::field_ref("b"),
         arrow::compute::call("equal", {arrow::compute::field_ref("a"),
                                        arrow::compute::field_ref("b")})},
        {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();

    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {EQ_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}

GTEST_TEST(DatasetComparisonTests, ComparisonNotEqual) {
    // 比较两列是否相等
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {EQ_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"), arrow::compute::field_ref("b"),
         arrow::compute::call("not_equal", {arrow::compute::field_ref("a"),
                                            arrow::compute::field_ref("b")})},
        {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();

    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {NOT_EQ_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}


GTEST_TEST(DatasetComparisonTests, ComparisonGreater) {
    // 比较左列是否大于右列
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {EQ_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"), arrow::compute::field_ref("b"),
         arrow::compute::call("greater", {arrow::compute::field_ref("a"),
                                            arrow::compute::field_ref("b")})},
        {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();

    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {GREATER_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}

GTEST_TEST(DatasetComparisonTests, ComparisonGreaterEqual) {
    // 比较左列是否大于等于右列
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {EQ_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"), arrow::compute::field_ref("b"),
         arrow::compute::call("greater_equal", {arrow::compute::field_ref("a"),
                                            arrow::compute::field_ref("b")})},
        {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();

    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {GREATER_EQ_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}


GTEST_TEST(DatasetComparisonTests, ComparisonLess) {
    // 比较左列是否小于右列
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {EQ_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"), arrow::compute::field_ref("b"),
         arrow::compute::call("less", {arrow::compute::field_ref("a"),
                                            arrow::compute::field_ref("b")})},
        {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();

    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {LESS_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}

GTEST_TEST(DatasetComparisonTests, ComparisonLessEqual) {
    // 比较左列是否小于等于右列
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {EQ_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"), arrow::compute::field_ref("b"),
         arrow::compute::call("less_equal", {arrow::compute::field_ref("a"),
                                            arrow::compute::field_ref("b")})},
        {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();

    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {LESS_EQ_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}
