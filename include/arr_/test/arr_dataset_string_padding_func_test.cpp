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

std::string const PAD_TABLE =  R"([
                                            {"a": "Hello World"},
                                            {"a": "Zhangsan"},
                                            {"a": "F4"},
                                            {"a": "Lisi"},
                                            {"a": "Wangwu"}
                                            ])";

std::string const PAD_CENTER_RES_TABLE =  R"([
                                            {"a": "Hello World", "res": "Hello World"},
                                            {"a": "Zhangsan", "res": "Zhangsan"},
                                            {"a": "F4", "res": " F4  "},
                                            {"a": "Lisi", "res": "Lisi "},
                                            {"a": "Wangwu", "res": "Wangwu"}
                                            ])";

std::string const PAD_LEFT_RES_TABLE =  R"([
                                            {"a": "Hello World", "res": "Hello World"},
                                            {"a": "Zhangsan", "res": "Zhangsan"},
                                            {"a": "F4", "res": "   F4"},
                                            {"a": "Lisi", "res": " Lisi"},
                                            {"a": "Wangwu", "res": "Wangwu"}
                                            ])";


std::string const PAD_RIGHT_RES_TABLE =  R"([
                                            {"a": "Hello World", "res": "Hello World"},
                                            {"a": "Zhangsan", "res": "Zhangsan"},
                                            {"a": "F4", "res": "F4   "},
                                            {"a": "Lisi", "res": "Lisi "},
                                            {"a": "Wangwu", "res": "Wangwu"}
                                            ])";
GTEST_TEST(DatasetStringPaddingTests, StrPadCenter) {
    // 居中，左右添加空字符
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {PAD_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    arrow::compute::PadOptions options{5};
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_center", {arrow::compute::field_ref("a")}, options)},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {PAD_CENTER_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   


GTEST_TEST(DatasetStringPaddingTests, StrPadLPad) {
    // 左边添加字符
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {PAD_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    arrow::compute::PadOptions options{5};
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_lpad", {arrow::compute::field_ref("a")}, options)},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {PAD_LEFT_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   


GTEST_TEST(DatasetStringPaddingTests, StrPadRPad) {
    // 右边添加字符
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {PAD_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    arrow::compute::PadOptions options{5};
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("ascii_rpad", {arrow::compute::field_ref("a")}, options)},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {PAD_RIGHT_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   