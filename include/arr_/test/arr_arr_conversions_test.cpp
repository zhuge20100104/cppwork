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

GTEST_TEST(ArrConversionsTests, CastIntToBool) {
    // int转换bool
    std::shared_ptr<arrow::Array> int_arr;
    arrow::ipc::internal::json::ArrayFromJSON(arrow::int32(), R"([1,2,3,4])", &int_arr);

    auto options = arrow::compute::CastOptions::Unsafe(arrow::boolean());

    auto eq_ = arrow::compute::CallFunction("cast", {int_arr}, &options);
    auto eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

// strptime 函数
GTEST_TEST(ArrConversionsTests, StrPTime) {
    // 字符串转时间
    std::shared_ptr<arrow::Array> str_arr;
    arrow::ipc::internal::json::ArrayFromJSON(arrow::utf8(), R"(["5/1/2020", "12/11/1900", "6/1/2021"])", &str_arr);

    arrow::compute::StrptimeOptions options("%m/%d/%Y", arrow::TimeUnit::MICRO);
    
    auto eq_ = arrow::compute::CallFunction("strptime", {str_arr}, &options);
    auto eq_array = eq_->array_as<arrow::TimestampArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}