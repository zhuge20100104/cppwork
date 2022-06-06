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


std::shared_ptr<arrow::Table> GenerateTable() {
    auto schema = ::arrow::schema({
      {arrow::field("a", arrow::float64())},
      {arrow::field("b", arrow::uint8())}
    });
    auto table = ArrowUtil::TableFromJSON(schema, {R"([
                                            {"a": 3.15, "b": 5},
                                            {"a": 3.36,  "b": 5},
                                            {"a": 3.14,  "b": 4},
                                            {"a": 2.71,  "b": 3},
                                            {"a": 3.28,  "b": 2},
                                            {"a": 3.23,  "b": 1}
                                            ])"});
    return table;
}

GTEST_TEST(DatasetLogarithmicTests, LogarithmicLn) {
    // 取某列的自然对数值
    auto const& tb =  GenerateTable();
    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("ln", {arrow::compute::field_ref("a")})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
} 

GTEST_TEST(DatasetLogarithmicTests, LogarithmicLog10) {
    // 取某列的Log10对数值
    auto const& tb =  GenerateTable();
    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("log10", {arrow::compute::field_ref("a")})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
} 

GTEST_TEST(DatasetLogarithmicTests, LogarithmicLog2) {
    // 取某列的Log2对数值
    auto const& tb =  GenerateTable();
    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("log2", {arrow::compute::field_ref("a")})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
} 
