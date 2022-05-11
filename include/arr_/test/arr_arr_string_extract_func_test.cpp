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


GTEST_TEST(ArrStringExtractTests, StrExtractRegex) {
    // 字符串正则表达式抽取 
    char const* json_path = "../data/s_extract.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);
    
    arrow::compute::ExtractRegexOptions options{"(?P<letter>[ab])(?P<digit>\\d)"};
    auto eq_ = arrow::compute::CallFunction("extract_regex", {array_a_res}, &options);

    auto eq_array = eq_->array_as<arrow::StructArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}