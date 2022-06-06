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
                                   {arrow::field("res", arrow::int32())}});

std::string const STR_TABLE =  R"([
                                            {"a": "hello"},
                                            {"a": "world"},
                                            {"a": "Zhangsan"},
                                            {"a": "Langping"}
                                            ])";

std::string const COUNT_RES_TABLE =  R"([
                                            {"a": "hello", "res": 0},
                                            {"a": "world", "res": 0},
                                            {"a": "Zhangsan", "res": 2},
                                            {"a": "Langping", "res": 1}
                                            ])";



GTEST_TEST(DatasetStringTrimmingTests, StrTrimLeft) {
    // 计算出现次数
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {STR_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    arrow::compute::MatchSubstringOptions options {"an"};
    scanner_builder->Project(
        {arrow::compute::field_ref("a"),
         arrow::compute::call("count_substring", {arrow::compute::field_ref("a")}, options)},
        {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {COUNT_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}   
