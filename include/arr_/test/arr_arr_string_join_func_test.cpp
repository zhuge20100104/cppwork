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


GTEST_TEST(ArrStringJoinTests, StrBinaryJoin) {
    // 单列字符串 List join 
    char const* json_path = "../data/s_join.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;

    arrow::PrettyPrint(tb_, {}, &std::cerr);
    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    arrow::compute::SplitPatternOptions options{","};
    auto ls_ = arrow::compute::CallFunction("split_pattern", {array_a_res}, &options);

    auto ls_array = ls_->array_as<arrow::ListArray>();
    arrow::PrettyPrint(*ls_array, {}, &std::cerr);

    auto join_ = arrow::compute::CallFunction("binary_join", {ls_array, arrow::Datum{"--"}});

    auto join_array = join_->array_as<arrow::StringArray>();
    arrow::PrettyPrint(*join_array, {}, &std::cerr);
}


GTEST_TEST(ArrStringJoinTests, StrBinaryJoinEleWise) {
    // 多列字符串join
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;

    arrow::PrettyPrint(tb_, {}, &std::cerr);
    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto array_b = tb_.GetColumnByName("s2");
    auto array_b_res = ArrowUtil::chunked_array_to_str_array(array_b);

    
    auto join_ = arrow::compute::CallFunction("binary_join_element_wise", {array_a_res, array_b_res, arrow::Datum{"--"}});

    auto join_array = join_->array_as<arrow::StringArray>();
    arrow::PrettyPrint(*join_array, {}, &std::cerr);
}
