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

GTEST_TEST(ArrStringTransTests, StrTransToLower) {
    // 某一列 转换成小写
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("ascii_lower", {array_a_res});
    auto eq_array = eq_->array_as<arrow::StringArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrStringTransTests, StrTransReverse) {
    // 某一列 反转
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("ascii_reverse", {array_a_res});
    auto eq_array = eq_->array_as<arrow::StringArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrStringTransTests, StrTransUpper) {
    // 某一列 转大写
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("ascii_upper", {array_a_res});
    auto eq_array = eq_->array_as<arrow::StringArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrStringTransTests, StrTransBinaryLen) {
    // 某一列 求长度
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("binary_length", {array_a_res});
    auto eq_array = eq_->array_as<arrow::Int32Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringTransTests, StrTransReplaceSubStr) {
    // 替换子字符串
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    arrow::compute::ReplaceSubstringOptions options {"ang", "C++"};
    auto eq_ = arrow::compute::CallFunction("replace_substring", {array_a_res}, &options);
    auto eq_array = eq_->array_as<arrow::StringArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringTransTests, StrTransReplaceSubStrRegex) {
    // 正则替换子字符串
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    arrow::compute::ReplaceSubstringOptions options {".*ang.*", "C++"};
    auto eq_ = arrow::compute::CallFunction("replace_substring_regex", {array_a_res}, &options);
    auto eq_array = eq_->array_as<arrow::StringArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringTransTests, StrTransUtf8Len) {
    // 某一列 Utf8 求长度
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("utf8_length", {array_a_res});
    auto eq_array = eq_->array_as<arrow::Int32Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringTransTests, StrTransUtf8Lower) {
    // 某一列 Utf8转换成小写
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("utf8_lower", {array_a_res});
    auto eq_array = eq_->array_as<arrow::StringArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


