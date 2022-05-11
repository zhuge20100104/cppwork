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

GTEST_TEST(ArrStringTrimTests, StrLTrim) {
    // 去除左边空格
    char const* json_path = "../data/s_trim.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);
    
    arrow::compute::TrimOptions options{" "};
    auto eq_ = arrow::compute::CallFunction("ascii_ltrim", {array_a_res}, &options);

    auto eq_array = eq_->array_as<arrow::StringArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrStringTrimTests, StrLTrimWhiteSpace) {
    // 去除左边空格
    char const* json_path = "../data/s_trim.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);
    
    auto eq_ = arrow::compute::CallFunction("ascii_ltrim_whitespace", {array_a_res});

    auto eq_array = eq_->array_as<arrow::StringArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrStringTrimTests, StrRTrim) {
    // 去除右边空格
    char const* json_path = "../data/s_trim.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);
    
    arrow::compute::TrimOptions options{" "};
    auto eq_ = arrow::compute::CallFunction("ascii_rtrim", {array_a_res}, &options);

    auto eq_array = eq_->array_as<arrow::StringArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrStringTrimTests, StrRTrimWhiteSpace) {
    // 去除右边空格
    char const* json_path = "../data/s_trim.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);
    
    auto eq_ = arrow::compute::CallFunction("ascii_rtrim_whitespace", {array_a_res});

    auto eq_array = eq_->array_as<arrow::StringArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringTrimTests, StrTrimAll) {
    // 去除左右空格
    char const* json_path = "../data/s_trim.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);
    
    arrow::compute::TrimOptions options {" "};
    auto eq_ = arrow::compute::CallFunction("ascii_trim", {array_a_res}, &options);

    auto eq_array = eq_->array_as<arrow::StringArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrStringTrimTests, StrTrimAllWhitespace) {
    // 去除左右空格
    char const* json_path = "../data/s_trim.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);
    
    arrow::compute::TrimOptions options {" "};
    auto eq_ = arrow::compute::CallFunction("ascii_trim_whitespace", {array_a_res}, &options);

    auto eq_array = eq_->array_as<arrow::StringArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringTrimTests, StrUtf8TrimAll) {
    // 去除左右空格
    char const* json_path = "../data/s_trim.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);
    
    arrow::compute::TrimOptions options {" "};
    auto eq_ = arrow::compute::CallFunction("utf8_trim", {array_a_res}, &options);

    auto eq_array = eq_->array_as<arrow::StringArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}