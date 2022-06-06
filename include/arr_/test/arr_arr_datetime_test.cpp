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


static std::shared_ptr<arrow::TimestampArray> get_date_time_arr() {
    std::shared_ptr<arrow::Array> str_arr;
    arrow::ipc::internal::json::ArrayFromJSON(arrow::utf8(), R"(["5/1/2020", "12/11/1900", "6/1/2021"])", &str_arr);

    arrow::compute::StrptimeOptions options("%m/%d/%Y", arrow::TimeUnit::MICRO);
    
    auto time_ = arrow::compute::CallFunction("strptime", {str_arr}, &options);
    auto time_array = time_->array_as<arrow::TimestampArray>();
    return time_array;
}

GTEST_TEST(ArrDateTimeTests, Year) {
    // 获取年月日中的年
    auto time_array = get_date_time_arr();
    auto year_ = arrow::compute::CallFunction("year", {time_array});
    
    auto year_array = year_->array_as<arrow::Int64Array>();
    arrow::PrettyPrint(*year_array, {}, &std::cerr);
}

GTEST_TEST(ArrDateTimeTests, Month) {
    // 获取年月日中的月
    auto time_array = get_date_time_arr();
    auto mon_ = arrow::compute::CallFunction("month", {time_array});
    
    auto mon_array = mon_->array_as<arrow::Int64Array>();
    arrow::PrettyPrint(*mon_array, {}, &std::cerr);
}


GTEST_TEST(ArrDateTimeTests, Day) {
    // 获取年月日中的日
    auto time_array = get_date_time_arr();
    auto day_ = arrow::compute::CallFunction("day", {time_array});
    
    auto day_array = day_->array_as<arrow::Int64Array>();
    arrow::PrettyPrint(*day_array, {}, &std::cerr);
}


GTEST_TEST(ArrDateTimeTests, DayOfWeek) {
    // 一天是一周中的第几天
    auto time_array = get_date_time_arr();
    arrow::compute::DayOfWeekOptions options;
    auto day_ = arrow::compute::CallFunction("day_of_week", {time_array}, &options);
    
    auto day_array = day_->array_as<arrow::Int64Array>();
    arrow::PrettyPrint(*day_array, {}, &std::cerr);
}

GTEST_TEST(ArrDateTimeTests, DayOfYear) {
    // 一天是1年中的第几天
    auto time_array = get_date_time_arr();
    auto day_ = arrow::compute::CallFunction("day_of_year", {time_array});
    
    auto day_array = day_->array_as<arrow::Int64Array>();
    arrow::PrettyPrint(*day_array, {}, &std::cerr);
}

GTEST_TEST(ArrDateTimeTests, Hour) {
    // 一天中当前的小时数
    auto time_array = get_date_time_arr();
    auto day_ = arrow::compute::CallFunction("hour", {time_array});
    
    auto day_array = day_->array_as<arrow::Int64Array>();
    arrow::PrettyPrint(*day_array, {}, &std::cerr);
}




