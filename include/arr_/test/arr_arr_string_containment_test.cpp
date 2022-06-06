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

GTEST_TEST(ArrStringContainmentTests, StrCountSubString) {
    // 计算子字符串 出现的次数
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    arrow::compute::MatchSubstringOptions options{"an"};
    auto eq_ = arrow::compute::CallFunction("count_substring", {array_a_res}, &options);
    std::shared_ptr<arrow::Int32Array> eq_array = eq_->array_as<arrow::Int32Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringContainmentTests, StrCountSubStringRegex) {
    // 计算正则子字符串 出现的次数 ang|an出现的次数
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    arrow::compute::MatchSubstringOptions options{"ang|an"};
    auto eq_ = arrow::compute::CallFunction("count_substring_regex", {array_a_res}, &options);
    std::shared_ptr<arrow::Int32Array> eq_array = eq_->array_as<arrow::Int32Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringContainmentTests, StrEndsWith) {
    // 计算字符串是否以某字符串结尾
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    arrow::compute::MatchSubstringOptions options{"san"};
    auto eq_ = arrow::compute::CallFunction("ends_with", {array_a_res}, &options);
   
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringContainmentTests, StrFindSubStr) {
    // 查找子字符串出现的位置
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    arrow::compute::MatchSubstringOptions options{"an"};
    auto eq_ = arrow::compute::CallFunction("find_substring", {array_a_res}, &options);
   
    std::shared_ptr<arrow::Int32Array> eq_array = eq_->array_as<arrow::Int32Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringContainmentTests, StrFindSubStrRegex) {
    // 查找子正则表达式 出现的位置
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    arrow::compute::MatchSubstringOptions options{"ang|an"};
    auto eq_ = arrow::compute::CallFunction("find_substring_regex", {array_a_res}, &options);
   
    std::shared_ptr<arrow::Int32Array> eq_array = eq_->array_as<arrow::Int32Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringContainmentTests, StrIndexIn) {
    // 返回 元素在数组中的索引, 如果没有就返回null
    char const* json_path = "../data/s_index.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    std::shared_ptr<arrow::Array> out;
    arrow::ipc::internal::json::ArrayFromJSON(arrow::utf8(), R"(["Tan tao","Zhang san"])", &out);
    arrow::compute::SetLookupOptions options{out};

    auto eq_ = arrow::compute::CallFunction("index_in", {array_a_res}, &options);
   
    std::shared_ptr<arrow::Int32Array> eq_array = eq_->array_as<arrow::Int32Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringContainmentTests, StrIsIn) {
    // 返回 返回元素是否在 Set中，如果是，就返回true,否则返回false
    char const* json_path = "../data/s_index.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    std::shared_ptr<arrow::Array> out;
    arrow::ipc::internal::json::ArrayFromJSON(arrow::utf8(), R"(["Tan tao"])", &out);
    arrow::compute::SetLookupOptions options{out};

    auto eq_ = arrow::compute::CallFunction("is_in", {array_a_res}, &options);
   
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringContainmentTests, StrMatchLike) {
    // 返回元素是否匹配SQL like表达式
    // %匹配任意多字符,_匹配 一个字符
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    arrow::compute::MatchSubstringOptions options{"%an%"};

    auto eq_ = arrow::compute::CallFunction("match_like", {array_a_res}, &options);
   
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrStringContainmentTests, StrMatchSubString) {
    // 返回是否存在匹配的子字符串
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    arrow::compute::MatchSubstringOptions options{"an"};    

    auto eq_ = arrow::compute::CallFunction("match_substring", {array_a_res}, &options);
   
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringContainmentTests, StrMatchSubStringRegex) {
    // 返回是否存在匹配的子字符串
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    arrow::compute::MatchSubstringOptions options{"an|ang"};    

    auto eq_ = arrow::compute::CallFunction("match_substring_regex", {array_a_res}, &options);
   
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrStringContainmentTests, StrStartsWith) {
    // 以某字符串 开始
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    arrow::compute::MatchSubstringOptions options{"Zha"};    

    auto eq_ = arrow::compute::CallFunction("starts_with", {array_a_res}, &options);
   
    std::shared_ptr<arrow::BooleanArray> eq_array = eq_->array_as<arrow::BooleanArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}








