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
      {arrow::field("a", arrow::int32())},
      {arrow::field("b", arrow::int32())}
    });
    auto table = ArrowUtil::TableFromJSON(schema, {R"([{"a": -1, "b": 5},
                                            {"a": 2,  "b": 3},
                                            {"a": -3, "b": null},
                                            {"a": -4, "b": null},
                                            {"a": 5,  "b": 5},
                                            {"a": 7,  "b": 5}
                                            ])"});
    return table;
}

GTEST_TEST(DatasetArithmeticTests, ProjectAbs) { 
    // 计算某个数字列的绝对值
    auto tb = GenerateTable();

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("abs", {arrow::compute::field_ref("a")})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}

GTEST_TEST(DatasetArithmeticTests, ProjectAdd) { 
    // 计算 两列数字相加的和
    auto tb = GenerateTable();

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("add", {arrow::compute::field_ref("a"), arrow::compute::field_ref("b")})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}

GTEST_TEST(DatasetArithmeticTests, ProjectDivide) { 
    // 计算 两列数字相除的值
    auto tb = GenerateTable();

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("divide", {arrow::compute::field_ref("a"), arrow::compute::field_ref("b")})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}

GTEST_TEST(DatasetArithmeticTests, ProjectMultiply) { 
    // 计算 两列数字相乘的值
    auto tb = GenerateTable();

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("multiply", {arrow::compute::field_ref("a"), arrow::compute::field_ref("b")})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}


GTEST_TEST(DatasetArithmeticTests, ProjectNegative) { 
    // 取负数
    auto tb = GenerateTable();

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("negate", {arrow::compute::field_ref("a")})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}


GTEST_TEST(DatasetArithmeticTests, ProjectPower) { 
    // N 次方
    auto tb = GenerateTable();

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("power", {arrow::compute::field_ref("a"), arrow::compute::literal(3)})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}

GTEST_TEST(DatasetArithmeticTests, ProjectSign) { 
    // 符号
    auto tb = GenerateTable();

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("sign", {arrow::compute::field_ref("a")})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}

GTEST_TEST(DatasetArithmeticTests, ProjectSubtract) { 
    // 减法
    auto tb = GenerateTable();

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::field_ref("b"),
        arrow::compute::call("subtract", {arrow::compute::field_ref("a"), arrow::compute::literal(3)})
    }, {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}

