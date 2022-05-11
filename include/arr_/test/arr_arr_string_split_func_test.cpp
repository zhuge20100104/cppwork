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

GTEST_TEST(ArrStringSplitTests, StrSplitWhitespace) {
    // 字符串分割
    char const* json_path = "../data/s_split.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);
    auto eq_ = arrow::compute::CallFunction("ascii_split_whitespace", {array_a_res});

    auto eq_array = eq_->array_as<arrow::ListArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrStringSplitTests, StrSplitPattern) {
    // 字符串按模式分割
    char const* json_path = "../data/s_split.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    arrow::compute::SplitPatternOptions options{" "};
    auto eq_ = arrow::compute::CallFunction("split_pattern", {array_a_res}, &options);

    auto eq_array = eq_->array_as<arrow::ListArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringSplitTests, StrSplitPatternRegex) {
    // 字符串按正则表达式分割
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    arrow::compute::SplitPatternOptions options{"ang|a"};
    auto eq_ = arrow::compute::CallFunction("split_pattern_regex", {array_a_res}, &options);

    auto eq_array = eq_->array_as<arrow::ListArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringSplitTests, StrSplitUtf8Whitespace) {
    // 字符串分割 Utf8
    char const* json_path = "../data/s_split.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);
    auto eq_ = arrow::compute::CallFunction("utf8_split_whitespace", {array_a_res});

    auto eq_array = eq_->array_as<arrow::ListArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}