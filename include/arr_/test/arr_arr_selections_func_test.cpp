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

GTEST_TEST(ArrSelectionsFuncTests, Filter) {
    // filter函数， 如果参数2是 true,就返回参数1中的元素
    // 输出 1,2
    std::shared_ptr<arrow::Array> values1, values2;
    arrow::ipc::internal::json::ArrayFromJSON(arrow::int32(), R"([1, 2,3,4])", &values1);
    
    arrow::ipc::internal::json::ArrayFromJSON(arrow::boolean(), R"([true,true,false,false])", &values2);
    
    auto options =  arrow::compute::FilterOptions::Defaults();
    auto eq_ = arrow::compute::CallFunction("filter", {values1, values2}, &options);
   
    auto eq_array = eq_->array_as<arrow::Int32Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrSelectionsFuncTests, Take) {
    // Take 函数，取前n个元素
    std::shared_ptr<arrow::Array> values1, indexies;
    arrow::ipc::internal::json::ArrayFromJSON(arrow::int32(), R"([1, 2,3,4])", &values1);

    arrow::ipc::internal::json::ArrayFromJSON(arrow::int32(), R"([2, 1,0,null])", &indexies);
    
    auto options =  arrow::compute::TakeOptions::Defaults();
    auto eq_ = arrow::compute::CallFunction("take", {values1, indexies}, &options);
   
    auto eq_array = eq_->array_as<arrow::Int32Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}
