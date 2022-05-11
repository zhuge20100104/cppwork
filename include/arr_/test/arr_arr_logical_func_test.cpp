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

GTEST_TEST(ArrLogicalTests, LogicalAnd) {
    // 两列bool类型与运算
    char const* json_path = "../data/dbl_bool.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("bool1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<bool, boolbuild, arrow::BooleanArray>(array_a);

    auto array_b = tb_.GetColumnByName("bool2");
    auto array_b_res = ArrowUtil::chunked_array_to_array<bool, boolbuild, arrow::BooleanArray>(array_b);

    auto and_ = arrow::compute::CallFunction("and", {array_a_res, array_b_res});

    auto and_value = and_->array_as<arrow::BooleanArray>();
 
    std::cout << and_value->ToString() << std::endl;
} 


GTEST_TEST(ArrLogicalTests, LogicalAndNot) {
    // 两列bool类型 And Not 运算
    // 先对第二列 not, 再and
    char const* json_path = "../data/dbl_bool.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("bool1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<bool, boolbuild, arrow::BooleanArray>(array_a);

    auto array_b = tb_.GetColumnByName("bool2");
    auto array_b_res = ArrowUtil::chunked_array_to_array<bool, boolbuild, arrow::BooleanArray>(array_b);

    auto and_ = arrow::compute::CallFunction("and_not", {array_a_res, array_b_res});

    auto and_value = and_->array_as<arrow::BooleanArray>();
 
    std::cout << and_value->ToString() << std::endl;
} 


GTEST_TEST(ArrLogicalTests, LogicalInvert) {
    // 单列bool类型反转
    char const* json_path = "../data/dbl_bool.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("bool1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<bool, boolbuild, arrow::BooleanArray>(array_a);

    auto invert_ = arrow::compute::CallFunction("invert", {array_a_res});

    auto invert_value = invert_->array_as<arrow::BooleanArray>();
 
    std::cout << invert_value->ToString() << std::endl;
} 


GTEST_TEST(ArrLogicalTests, LogicalOr) {
    // 两列bool类型 取或
    char const* json_path = "../data/dbl_bool.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("bool1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<bool, boolbuild, arrow::BooleanArray>(array_a);

    auto array_b = tb_.GetColumnByName("bool2");
    auto array_b_res = ArrowUtil::chunked_array_to_array<bool, boolbuild, arrow::BooleanArray>(array_b);

    auto or_ = arrow::compute::CallFunction("or", {array_a_res, array_b_res});

    auto or_value = or_->array_as<arrow::BooleanArray>();
 
    std::cout << or_value->ToString() << std::endl;
} 



GTEST_TEST(ArrLogicalTests, LogicalXor) {
    // 两列bool类型 取异或
    char const* json_path = "../data/dbl_bool.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    
    auto array_a = tb_.GetColumnByName("bool1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<bool, boolbuild, arrow::BooleanArray>(array_a);

    auto array_b = tb_.GetColumnByName("bool2");
    auto array_b_res = ArrowUtil::chunked_array_to_array<bool, boolbuild, arrow::BooleanArray>(array_b);

    auto or_ = arrow::compute::CallFunction("xor", {array_a_res, array_b_res});

    auto or_value = or_->array_as<arrow::BooleanArray>();
 
    std::cout << or_value->ToString() << std::endl;
} 




