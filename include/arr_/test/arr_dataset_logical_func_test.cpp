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
    {{arrow::field("a", arrow::boolean())}, {arrow::field("b", arrow::boolean())}});

auto DST_SCHEMA = ::arrow::schema({{arrow::field("a", arrow::boolean())},
                                   {arrow::field("b", arrow::boolean())},
                                   {arrow::field("res", arrow::boolean())}});

std::string const AND_TABLE =  R"([
                                            {"a": true, "b": true},
                                            {"a": true,  "b": true},
                                            {"a": true,  "b": false},
                                            {"a": true,  "b": false},
                                            {"a": false,  "b": false}
                                            ])";

std::string const AND_RES_TABLE =  R"([
                                            {"a": true, "b": true, "res": true},
                                            {"a": true,  "b": true, "res": true},
                                            {"a": true,  "b": false, "res": false},
                                            {"a": true,  "b": false, "res": false},
                                            {"a": false,  "b": false, "res": false}
                                            ])";


std::string const AND_NOT_RES_TABLE =  R"([
                                            {"a": true, "b": true, "res": false},
                                            {"a": true,  "b": true, "res": false},
                                            {"a": true,  "b": false, "res": true},
                                            {"a": true,  "b": false, "res": true},
                                            {"a": false,  "b": false, "res": false}
                                            ])";

std::string const INVERT_RES_TABLE =  R"([
                                            {"a": true, "b": true, "res": false},
                                            {"a": true,  "b": true, "res": false},
                                            {"a": true,  "b": false, "res": false},
                                            {"a": true,  "b": false, "res": false},
                                            {"a": false,  "b": false, "res": true}
                                            ])";

std::string const OR_RES_TABLE =  R"([
                                            {"a": true, "b": true, "res": true},
                                            {"a": true,  "b": true, "res": true},
                                            {"a": true,  "b": false, "res": true},
                                            {"a": true,  "b": false, "res": true},
                                            {"a": false,  "b": false, "res": false}
                                            ])";

std::string const XOR_RES_TABLE =  R"([
                                            {"a": true, "b": true, "res": false},
                                            {"a": true,  "b": true, "res": false},
                                            {"a": true,  "b": false, "res": true},
                                            {"a": true,  "b": false, "res": true},
                                            {"a": false,  "b": false, "res": false}
                                            ])";

GTEST_TEST(DatasetLogicalTests, LogicalAnd) {
    // 两列bool类型与运算
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {AND_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"), arrow::compute::field_ref("b"),
         arrow::compute::call("and", {arrow::compute::field_ref("a"),
                                            arrow::compute::field_ref("b")})},
        {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {AND_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   

GTEST_TEST(DatasetLogicalTests, LogicalAndNot) {
     // 两列bool类型 And Not 运算
    // 先对第二列 not, 再and
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {AND_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"), arrow::compute::field_ref("b"),
         arrow::compute::call("and_not", {arrow::compute::field_ref("a"),
                                            arrow::compute::field_ref("b")})},
        {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {AND_NOT_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   

GTEST_TEST(DatasetLogicalTests, LogicalInvert) {
     // bool类型 Revert 运算, 取反
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {AND_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"), arrow::compute::field_ref("b"),
         arrow::compute::call("invert", {arrow::compute::field_ref("a")})},
        {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {INVERT_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   

GTEST_TEST(DatasetLogicalTests, LogicalOr) {
     // bool类型 或运算
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {AND_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"), arrow::compute::field_ref("b"),
         arrow::compute::call("or", {arrow::compute::field_ref("a"), arrow::compute::field_ref("b")})},
        {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {OR_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}  

GTEST_TEST(DatasetLogicalTests, LogicalXor) {
     // bool类型 异或运算
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {AND_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"), arrow::compute::field_ref("b"),
         arrow::compute::call("xor", {arrow::compute::field_ref("a"), arrow::compute::field_ref("b")})},
        {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {XOR_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}  


