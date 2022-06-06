#include "arr_/arr_.h"
#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include <gtest/gtest.h>


#include <iostream>
#include <vector>
#include <limits>

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

auto const SRC_SCHEMA = ::arrow::schema({
                                        {arrow::field("a", arrow::float64())}
                                        });

auto const DST_SCHEMA = ::arrow::schema({
                                        {arrow::field("a", arrow::float64())},
                                        {arrow::field("res", arrow::float64())}
                                        });

std::string const COS_TABLE = R"([
                                    {"a": 1.0},
                                    {"a": 0.0}
                                ])";

std::string const COS_RES_TABLE = R"([
                                    {"a": 1.0, "res": 0},
                                    {"a": 0.0, "res": 1.5707963267948966}
                                ])";


std::string const SIN_TABLE = R"([
                                    {"a": 1.0},
                                    {"a": 0.0}
                                ])";

std::string const SIN_RES_TABLE = R"([
                                    {"a": 1.0, "res": 1.5707963267948966},
                                    {"a": 0.0, "res": 0}
                                ])";

std::string const TAN_TABLE = R"([
                                    {"a": 1.0},
                                    {"a": 0.0}
                                ])";

std::string const TAN_RES_TABLE = R"([
                                    {"a": 1.0, "res": 0.78539816339744828},
                                    {"a": 0.0, "res": 0}
                                ])";      

std::string const COS_VAL_TABLE = R"([
                                    {"a": 0.0},
                                    {"a": 1.047197551196598}
                                ])";

std::string const COS_VAL_RES_TABLE = R"([
                                    {"a": 0.0, "res": 1},
                                    {"a": 1.047197551196598, "res": 0.49999999999999972}
                                ])";      


std::string const SIN_VAL_TABLE = R"([
                                    {"a": 0.0},
                                    {"a": 1.5707963267948966}
                                ])";

std::string const SIN_VAL_RES_TABLE = R"([
                                    {"a": 0.0, "res": 0},
                                    {"a":  1.5707963267948966, "res": 1}
                                ])";      


std::string const TAN_VAL_TABLE = R"([
                                    {"a": 0.0},
                                    {"a": 0.78539815}
                                ])";

std::string const TAN_VAL_RES_TABLE = R"([
                                    {"a": 0.0, "res": 0},
                                    {"a": 0.78539815, "res": 0.99999997320510381}
                                ])";      

GTEST_TEST(DatasetTriangleTests, TriangleAcos) {
    // 三角函数Acos值
    auto const& tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {COS_TABLE});
    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::call("acos", {arrow::compute::field_ref("a")})
    }, {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie(); 
    auto const& tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {COS_RES_TABLE});
    
    std::cerr.precision(std::numeric_limits<double>::max_digits10);
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    arrow::PrettyPrint(*tb_res, {}, &std::cerr);
    
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
} 

GTEST_TEST(DatasetTriangleTests, TriangleASin) {
    // 三角函数Asin值
    auto const& tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {SIN_TABLE});
    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::call("asin", {arrow::compute::field_ref("a")})
    }, {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie(); 
    auto const& tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {SIN_RES_TABLE});
    
    std::cerr.precision(std::numeric_limits<double>::max_digits10);
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    arrow::PrettyPrint(*tb_res, {}, &std::cerr);
    
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
} 


GTEST_TEST(DatasetTriangleTests, TriangleATan) {
    // 三角函数ATan值
    auto const& tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {TAN_TABLE});
    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::call("atan", {arrow::compute::field_ref("a")})
    }, {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie(); 
    auto const& tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {TAN_RES_TABLE});
    
    std::cerr.precision(std::numeric_limits<double>::max_digits10);
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    arrow::PrettyPrint(*tb_res, {}, &std::cerr);
    
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
} 


GTEST_TEST(DatasetTriangleTests, TriangleCosVal) {
    // 三角函数Cos值
    auto const& tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {COS_VAL_TABLE});
    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::call("cos", {arrow::compute::field_ref("a")})
    }, {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie(); 
    auto const& tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {COS_VAL_RES_TABLE});
    
    std::cerr.precision(std::numeric_limits<double>::max_digits10);
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    arrow::PrettyPrint(*tb_res, {}, &std::cerr);
    
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
} 


GTEST_TEST(DatasetTriangleTests, TriangleSinVal) {
    // 三角函数Sin值
    auto const& tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {SIN_VAL_TABLE});
    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::call("sin", {arrow::compute::field_ref("a")})
    }, {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie(); 
    auto const& tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {SIN_VAL_RES_TABLE});
    
    std::cerr.precision(std::numeric_limits<double>::max_digits10);
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    arrow::PrettyPrint(*tb_res, {}, &std::cerr);
    
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
} 


GTEST_TEST(DatasetTriangleTests, TriangleTanVal) {
    // 三角函数Tan值
    auto const& tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {TAN_VAL_TABLE});
    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("a"),
        arrow::compute::call("tan", {arrow::compute::field_ref("a")})
    }, {"a", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie(); 
    auto const& tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {TAN_VAL_RES_TABLE});
    
    std::cerr.precision(std::numeric_limits<double>::max_digits10);
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    arrow::PrettyPrint(*tb_res, {}, &std::cerr);
    
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
} 
