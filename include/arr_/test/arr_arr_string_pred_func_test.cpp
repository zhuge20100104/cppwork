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


GTEST_TEST(ArrStringPredTests, StrPredIsAlnum) {
    // 某一列是否ASCII的字母或数字
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("ascii_is_alnum", {array_a_res});
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrStringPredTests, StrPredIsAlpha) {
    // 某一列是否ASCII的字母
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("ascii_is_alpha", {array_a_res});
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringPredTests, StrPredIsDecimal) {
    // 某一列是否是浮点数
    char const* json_path = "../data/decimal_str.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("d1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("ascii_is_decimal", {array_a_res});
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrStringPredTests, StrPredIsLower) {
    // 某一列是否是小写字母
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("ascii_is_lower", {array_a_res});
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrStringPredTests, StrPredIsPrintable) {
    // 某一列是否 可打印字符
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("ascii_is_printable", {array_a_res});
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringPredTests, StrPredIsSpace) {
    // 某一列是否 为空格
    char const* json_path = "../data/space.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("sp1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("ascii_is_space", {array_a_res});
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringPredTests, StrPredIsUpper) {
    // 某一列是否 为大写字母
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("ascii_is_upper", {array_a_res});
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringPredTests, StrPredIsUtf8Alnum) {
    // 某一列是否UTF8 的字母或数字
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("utf8_is_alnum", {array_a_res});
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrStringPredTests, StrPredIsUtf8Alpha) {
    // 某一列是否Utf8的字母
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("utf8_is_alpha", {array_a_res});
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringPredTests, StrPredIsUtf8Decimal) {
    // 某一列是否是浮点数
    char const* json_path = "../data/decimal_str.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("d1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("utf8_is_decimal", {array_a_res});
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrStringPredTests, StrPredIsAscTitle) {
    // 某一列是否是 ASCII Title
    char const* json_path = "../data/title.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("asc");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("ascii_is_title", {array_a_res});
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrStringPredTests, StrPredIsUtf8Title) {
    // 某一列是否是Utf8的title
    char const* json_path = "../data/title.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("utf");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("utf8_is_title", {array_a_res});
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrStringPredTests, StrPredIsAscii) {
    // 某一列是否是Ascii字符
    char const* json_path = "../data/title.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("asc");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto eq_ = arrow::compute::CallFunction("string_is_ascii", {array_a_res});
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}