#include "arr_/arr_.h"
#include <memory>
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
                                            {"a": 1.2, "b": 5},
                                            {"a": 1.3,  "b": 5},
                                            {"a": 2.5,  "b": 4},
                                            {"a": 3.6,  "b": 3},
                                            {"a": 4.1,  "b": 2},
                                            {"a": 5.2,  "b": 1}
                                            ])"});
    return table;
}


GTEST_TEST(DatasetRoundingTests, Floor) { 
    // 向下取整
    auto tb = GenerateTable();

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("floor", {arrow::compute::field_ref("a")})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}

GTEST_TEST(DatasetRoundingTests, Ceil) { 
    // 向上取整
    auto tb = GenerateTable();

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("ceil", {arrow::compute::field_ref("a")})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}


GTEST_TEST(DatasetRoundingTests, Trunc) { 
    // 截断
    auto tb = GenerateTable();

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("trunc", {arrow::compute::field_ref("a")})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}
