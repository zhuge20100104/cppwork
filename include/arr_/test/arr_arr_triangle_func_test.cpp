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

GTEST_TEST(ArrTriangleTests, TriangleAcos) {
    // 求acos值
    char const* json_path = "../data/triangle_val.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("f1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<double, numbuildT<arrow::DoubleType>, arrow::DoubleArray>(array_a);

   
    auto abs_arr = arrow::compute::CallFunction("acos", {array_a_res});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::DoubleArray>();
 
    std::cout << abs_value->ToString() << std::endl;
} 


GTEST_TEST(ArrTriangleTests, TriangleASin) {
    // 求asin值
    char const* json_path = "../data/triangle_val.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("f1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<double, numbuildT<arrow::DoubleType>, arrow::DoubleArray>(array_a);

   
    auto abs_arr = arrow::compute::CallFunction("asin", {array_a_res});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::DoubleArray>();
 
    std::cout << abs_value->ToString() << std::endl;
} 


GTEST_TEST(ArrTriangleTests, TriangleATan) {
    // 求atan值
    char const* json_path = "../data/triangle_val.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("f1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<double, numbuildT<arrow::DoubleType>, arrow::DoubleArray>(array_a);

   
    auto abs_arr = arrow::compute::CallFunction("atan", {array_a_res});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::DoubleArray>();
 
    std::cout << abs_value->ToString() << std::endl;
} 


GTEST_TEST(ArrTriangleTests, TriangleCos) {
    // 求cos值
    char const* json_path = "../data/triangle_val2.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("f1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<double, numbuildT<arrow::DoubleType>, arrow::DoubleArray>(array_a);

   
    auto abs_arr = arrow::compute::CallFunction("cos", {array_a_res});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::DoubleArray>();
 
    std::cout << abs_value->ToString() << std::endl;
} 


GTEST_TEST(ArrTriangleTests, TriangleSin) {
    // 求sin值
    char const* json_path = "../data/triangle_val2.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("f1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<double, numbuildT<arrow::DoubleType>, arrow::DoubleArray>(array_a);

   
    auto abs_arr = arrow::compute::CallFunction("sin", {array_a_res});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::DoubleArray>();
 
    std::cout << abs_value->ToString() << std::endl;
} 

GTEST_TEST(ArrTriangleTests, TriangleTan) {
    // 求tan值
    char const* json_path = "../data/triangle_val3.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("f1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<double, numbuildT<arrow::DoubleType>, arrow::DoubleArray>(array_a);

   
    auto abs_arr = arrow::compute::CallFunction("tan", {array_a_res});
    // Unpack boolean scalar result (a one-field scalar)
    auto abs_value = abs_arr->array_as<arrow::DoubleArray>();
 
    std::cout << abs_value->ToString() << std::endl;
} 


