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

GTEST_TEST(ArrComparisonTests, ComparisonEqual) {
    // 比较两列是否相等
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto array_b= tb_.GetColumnByName("int2");
    auto array_b_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_b);

    auto eq_arr = arrow::compute::CallFunction("equal", {array_a_res, array_b_res});

    auto eq_value = eq_arr->array_as<arrow::BooleanArray>();
 
    std::cout << eq_value->ToString() << std::endl;
} 

GTEST_TEST(ArrComparisonTests, ComparisonGreater) {
    // 比较两列是否大于
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto array_b= tb_.GetColumnByName("int2");
    auto array_b_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_b);

    auto eq_arr = arrow::compute::CallFunction("greater", {array_a_res, array_b_res});

    auto eq_value = eq_arr->array_as<arrow::BooleanArray>();
 
    std::cout << eq_value->ToString() << std::endl;
} 

GTEST_TEST(ArrComparisonTests, ComparisonGreaterEqual) {
    // 比较两列是否大于等于
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto array_b= tb_.GetColumnByName("int2");
    auto array_b_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_b);

    auto eq_arr = arrow::compute::CallFunction("greater_equal", {array_a_res, array_b_res});

    auto eq_value = eq_arr->array_as<arrow::BooleanArray>();
 
    std::cout << eq_value->ToString() << std::endl;
} 


GTEST_TEST(ArrComparisonTests, ComparisonLess) {
    // 比较两列是否小于
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto array_b= tb_.GetColumnByName("int2");
    auto array_b_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_b);

    auto eq_arr = arrow::compute::CallFunction("less", {array_a_res, array_b_res});

    auto eq_value = eq_arr->array_as<arrow::BooleanArray>();
 
    std::cout << eq_value->ToString() << std::endl;
} 

GTEST_TEST(ArrComparisonTests, ComparisonLessEqual) {
    // 比较两列是否小于等于
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto array_b= tb_.GetColumnByName("int2");
    auto array_b_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_b);

    auto eq_arr = arrow::compute::CallFunction("less_equal", {array_a_res, array_b_res});

    auto eq_value = eq_arr->array_as<arrow::BooleanArray>();
 
    std::cout << eq_value->ToString() << std::endl;
} 


GTEST_TEST(ArrComparisonTests, ComparisonMaxEle) {
    // 获取多列最大值
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto array_b= tb_.GetColumnByName("int2");
    auto array_b_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_b);

    auto array_c = tb_.GetColumnByName("int3");
    auto array_c_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_c);

    auto max_arr = arrow::compute::CallFunction("max_element_wise", {array_a_res, array_b_res, array_c_res});

    auto max_value = max_arr->array_as<arrow::Int64Array>();
 
    std::cout << max_value->ToString() << std::endl;
} 


GTEST_TEST(ArrComparisonTests, ComparisonMinEle) {
    // 获取多列最小值
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto array_b= tb_.GetColumnByName("int2");
    auto array_b_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_b);

    auto array_c = tb_.GetColumnByName("int3");
    auto array_c_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_c);

    auto max_arr = arrow::compute::CallFunction("min_element_wise", {array_a_res, array_b_res, array_c_res});

    auto max_value = max_arr->array_as<arrow::Int64Array>();
 
    std::cout << max_value->ToString() << std::endl;
} 