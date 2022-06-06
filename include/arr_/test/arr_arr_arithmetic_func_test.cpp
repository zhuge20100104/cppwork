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

GTEST_TEST(ArrArithmeticTests, ArithmeticAbs) {
    // 计算 int1列的绝对值
    char const* json_path = "../data/abs_num.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto abs_arr = arrow::compute::CallFunction("abs", {array_a_res});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::Int64Array>();
 
    std::cout << abs_value->ToString() << std::endl;
} 

GTEST_TEST(ArrArithmeticTests, ArithmeticAbsChecked) {
    // 计算 int1列的绝对值， 检查overflow，当越界时，直接返回原值
    char const* json_path = "../data/abs_num.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto abs_arr = arrow::compute::CallFunction("abs_checked", {array_a_res});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::Int64Array>();
 
    std::cout << abs_value->ToString() << std::endl;
} 

GTEST_TEST(ArrArithmeticTests, ArithmeticAddChecked) {
    // 加法方法, 检查越界，越界时，Status设置为overflow
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto abs_arr = arrow::compute::CallFunction("add_checked", {array_a_res, arrow::Datum(3)});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::Int64Array>();
 
    std::cout << abs_value->ToString() << std::endl;
} 


GTEST_TEST(ArrArithmeticTests, ArithmeticDivide) {
    // 除法
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto abs_arr = arrow::compute::CallFunction("divide", {array_a_res, arrow::Datum(0.5)});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::DoubleArray>();
 
    std::cout << abs_value->ToString() << std::endl;
} 


GTEST_TEST(ArrArithmeticTests, ArithmeticMultiple) {
    // 乘法
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto abs_arr = arrow::compute::CallFunction("multiply", {array_a_res, arrow::Datum(3)});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::Int64Array>();
 
    std::cout << abs_value->ToString() << std::endl;
} 

GTEST_TEST(ArrArithmeticTests, ArithmeticNegate) {
    // 取反
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto abs_arr = arrow::compute::CallFunction("negate", {array_a_res});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::Int64Array>();
 
    std::cout << abs_value->ToString() << std::endl;
} 

GTEST_TEST(ArrArithmeticTests, ArithmeticPower) {
    // N次方
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto abs_arr = arrow::compute::CallFunction("power", {array_a_res, arrow::Datum{3}});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::Int64Array>();
 
    std::cout << abs_value->ToString() << std::endl;
} 

GTEST_TEST(ArrArithmeticTests, ArithmeticSign) {
    // 取符号
    // -1 负数， +1 正数， 0 zero, NaN Nan
    char const* json_path = "../data/abs_num.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto abs_arr = arrow::compute::CallFunction("sign", {array_a_res});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::Int8Array>();
 
    std::cout << abs_value->ToString() << std::endl;
} 

GTEST_TEST(ArrArithmeticTests, ArithmeticSubstract) {
    // 减法
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto abs_arr = arrow::compute::CallFunction("subtract", {array_a_res, arrow::Datum{1}});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::Int64Array>();
 
    std::cout << abs_value->ToString() << std::endl;
} 







