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

GTEST_TEST(ArrLogarithmicTests, LogarithmicLn) {
    // 取某列的自然对数值
    char const* json_path = "../data/floating_val.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("f1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<double, numbuildT<arrow::DoubleType>, arrow::DoubleArray>(array_a);

   
    auto abs_arr = arrow::compute::CallFunction("ln", {array_a_res});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::DoubleArray>();
 
    std::cout << abs_value->ToString() << std::endl;
} 


GTEST_TEST(ArrLogarithmicTests, LogarithmicLog10) {
    // 取某列的Log10对数值
    char const* json_path = "../data/floating_val.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("f1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<double, numbuildT<arrow::DoubleType>, arrow::DoubleArray>(array_a);

   
    auto abs_arr = arrow::compute::CallFunction("log10", {array_a_res});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::DoubleArray>();
 
    std::cout << abs_value->ToString() << std::endl;
} 


GTEST_TEST(ArrLogarithmicTests, LogarithmicLog2) {
    // 取某列的log2 对数值
    char const* json_path = "../data/floating_val.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("f1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<double, numbuildT<arrow::DoubleType>, arrow::DoubleArray>(array_a);

   
    auto abs_arr = arrow::compute::CallFunction("log2", {array_a_res});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::DoubleArray>();
 
    std::cout << abs_value->ToString() << std::endl;
} 


