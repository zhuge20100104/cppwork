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

GTEST_TEST(ArrBitwiseTests, BitwiseAnd) {
    // 按位与运算
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    auto array_b = tb_.GetColumnByName("int2");
    auto array_b_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_b);

    auto bit_arr = arrow::compute::CallFunction("bit_wise_and", {array_a_res, array_b_res});
    // Unpack boolean scalar result (a one-field scalar)
    auto bit_value = bit_arr->array_as<arrow::Int64Array>();
 
    std::cout << bit_value->ToString() << std::endl;
}