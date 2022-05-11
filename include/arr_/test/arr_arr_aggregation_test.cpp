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

GTEST_TEST(ArrAggregationTests, AggregateAll) {
    // 计算bool1列是否都为true
    char const* json_path = "../data/bool_ts.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("bool1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<bool, boolbuild, arrow::BooleanArray>(array_a);

    arrow::compute::ScalarAggregateOptions scalar_aggregate_options;
    scalar_aggregate_options.skip_nulls = false;

    auto all_ = arrow::compute::CallFunction("all", {array_a_res}, &scalar_aggregate_options);
    // Unpack boolean scalar result (a one-field scalar)
    auto all_value = all_->scalar_as<arrow::BooleanScalar>().value;
 
    std::cout << all_value << std::endl;
} 

GTEST_TEST(ArrAggregationTests, AggregateAny) {
    // 计算bool1列 是否有一个为true
    char const* json_path = "../data/bool_ts.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("bool1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<bool, boolbuild, arrow::BooleanArray>(array_a);

    arrow::compute::ScalarAggregateOptions scalar_aggregate_options;
    scalar_aggregate_options.skip_nulls = false;

    auto any_ = arrow::compute::CallFunction("any", {array_a_res}, &scalar_aggregate_options);
    // Unpack boolean scalar result (a one-field scalar)
    auto any_value = any_->scalar_as<arrow::BooleanScalar>().value;
 
    std::cout << any_value << std::endl;
} 

GTEST_TEST(ArrAggregationTests, AggregateCount) {
    // 查看int1列共有多少行
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto count_ = arrow::compute::CallFunction("count", {array_a_res});
    // Unpack int64 scalar result (a one-field scalar)
    auto count_value = count_->scalar_as<arrow::Int64Scalar>().value;
 
    std::cout << count_value << std::endl;
} 


GTEST_TEST(ArrAggregationTests, AggregateIndex) {
    // 查看int1列共有多少行
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);
    
    arrow::compute::IndexOptions options;
    options.value = std::make_shared<arrow::Int64Scalar>(7);

    auto index_ = arrow::compute::CallFunction("index", {array_a_res}, &options);
    // Unpack int64 scalar result (a one-field scalar)
    auto index_value = index_->scalar_as<arrow::Int64Scalar>().value;
 
    std::cout << index_value << std::endl;
} 

GTEST_TEST(ArrAggregationTests, AggregateMode) {
    // 查看int1 里面的top-n
    // 3 出现了 4 次，2 出现了3次
    char const* json_path = "../data/top_n.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);
    
    arrow::compute::ModeOptions options;
    options.n = 2;

    auto mode_ = arrow::compute::CallFunction("mode", {array_a_res}, &options);
   
    auto mode_value = mode_->array_as<arrow::StructArray>();
    std::cout << mode_value->ToString() << std::endl;
} 

GTEST_TEST(ArrAggregationTests, AggregateStdDev) {
    // 求方差
    char const* json_path = "../data/top_n.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto stddev_ = arrow::compute::CallFunction("stddev", {array_a_res});   
    auto stddev_value = stddev_->scalar_as<arrow::DoubleScalar>().value;
    std::cout << stddev_value << std::endl;
} 

GTEST_TEST(ArrAggregationTests, AggregateSum) {
    // 求和
    char const* json_path = "../data/top_n.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto sum_ = arrow::compute::CallFunction("sum", {array_a_res});   
    auto sum_value = sum_->scalar_as<arrow::Int64Scalar>().value;
    std::cout << sum_value << std::endl;
} 










