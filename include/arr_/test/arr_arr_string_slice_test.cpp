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

GTEST_TEST(ArrStringSliceTests, StrSlice) {
    // 字符串切割
    char const* json_path = "../data/s_join.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    arrow::compute::SliceOptions options {2, 5};
    auto eq_ = arrow::compute::CallFunction("utf8_slice_codeunits", {array_a_res}, &options);
    std::shared_ptr<arrow::StringArray> eq_array = eq_->array_as<arrow::StringArray>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}
