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


static std::shared_ptr<arrow::Array> get_list_array() {
    std::shared_ptr<arrow::Array> list_array;
    arrow::ipc::internal::json::ArrayFromJSON(arrow::int32(), "[1,2,2,4,5,8,9,9,11]", &list_array);
    return list_array;
}


GTEST_TEST(ArrArrayWiseTests, DictEncode) {
    // 字典编码
    auto ls_array = get_list_array();
    auto res_ = arrow::compute::CallFunction("dictionary_encode", {ls_array});
    
    auto res_array = res_->array_as<arrow::DictionaryArray>();
    arrow::PrettyPrint(*res_array, {}, &std::cerr);
}

GTEST_TEST(ArrArrayWiseTests, Unique) {
    // 求唯一值
    auto ls_array = get_list_array();
    auto res_ = arrow::compute::CallFunction("unique", {ls_array});
    
    auto res_array = res_->array_as<arrow::Int32Array>();
    arrow::PrettyPrint(*res_array, {}, &std::cerr);
}

GTEST_TEST(ArrArrayWiseTests, ValueCounts) {
    // 求每个值出现的次数
    auto ls_array = get_list_array();
    auto res_ = arrow::compute::CallFunction("value_counts", {ls_array});
   
    auto res_array = res_->array_as<arrow::StructArray>();
    arrow::PrettyPrint(*res_array, {}, &std::cerr);
}