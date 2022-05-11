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
      {arrow::field("a", arrow::uint8())},
      {arrow::field("b", arrow::uint8())}
    });
    auto table = ArrowUtil::TableFromJSON(schema, {R"([
                                            {"a": 1, "b": 5},
                                            {"a": 1,  "b": 5},
                                            {"a": 2,  "b": 4},
                                            {"a": 3,  "b": 3},
                                            {"a": 4,  "b": 2},
                                            {"a": 5,  "b": 1}
                                            ])"});
    return table;
}

GTEST_TEST(DatasetBitwiseTests, BitwiseAnd) { 
    // 计算某个数字列的绝对值
    auto tb = GenerateTable();

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("bit_wise_and", {arrow::compute::field_ref("a"), arrow::compute::field_ref("b")})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}


GTEST_TEST(DatasetBitwiseTests, BitwiseNot) { 
    // 按位取反
    auto tb = GenerateTable();

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("bit_wise_not", {arrow::compute::field_ref("a")})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}


GTEST_TEST(DatasetBitwiseTests, BitwiseOr) { 
    // 按位或
    auto tb = GenerateTable();

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("bit_wise_or", {arrow::compute::field_ref("a"), arrow::compute::field_ref("b")})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}

GTEST_TEST(DatasetBitwiseTests, BitwiseXor) { 
    // 按位异或
    auto tb = GenerateTable();

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("bit_wise_xor", {arrow::compute::field_ref("a"), arrow::compute::field_ref("b")})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}


GTEST_TEST(DatasetBitwiseTests, BitwiseShiftLeft) { 
    // 按位左移
    auto tb = GenerateTable();

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("shift_left", {arrow::compute::field_ref("a"), arrow::compute::literal(1)})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}


GTEST_TEST(DatasetBitwiseTests, BitwiseShiftRight) { 
    // 按位右移
    auto tb = GenerateTable();

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("shift_right", {arrow::compute::field_ref("a"), arrow::compute::literal(1)})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}

