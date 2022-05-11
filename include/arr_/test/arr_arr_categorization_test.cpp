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

GTEST_TEST(ArrCategorizationTests, IsFinite) {
    // 是否有限数字
    char const* json_path = "../data/inf_num.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("f1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<double, numbuildT<arrow::DoubleType>, arrow::DoubleArray>(array_a);

    auto eq_ = arrow::compute::CallFunction("is_finite", {array_a_res});
   
    auto eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrCategorizationTests, IsInf) {
    // 是否无限数字
    char const* json_path = "../data/inf_num.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("f1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<double, numbuildT<arrow::DoubleType>, arrow::DoubleArray>(array_a);

    auto eq_ = arrow::compute::CallFunction("is_inf", {array_a_res});
   
    auto eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrCategorizationTests, IsNan) {
    // 是否是Nan
    char const* json_path = "../data/inf_num.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("f1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<double, numbuildT<arrow::DoubleType>, arrow::DoubleArray>(array_a);

    auto eq_ = arrow::compute::CallFunction("is_nan", {array_a_res});
   
    auto eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrCategorizationTests, IsNull) {
    // 是否是Null
    auto array_a_res = std::make_shared<arrow::NullArray>(5);

    auto eq_ = arrow::compute::CallFunction("is_null", {array_a_res});
   
    auto eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrCategorizationTests, IsValid) {
    // 是否可用
    auto array_a_res = std::make_shared<arrow::NullArray>(5);

    auto eq_ = arrow::compute::CallFunction("is_valid", {array_a_res});
   
    auto eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


