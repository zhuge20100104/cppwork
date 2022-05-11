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

GTEST_TEST(ArrStructTransTests, ListFlatten) {
    // 列表拍平
    std::shared_ptr<arrow::Array> list_array;
    arrow::ipc::internal::json::ArrayFromJSON(arrow::list(arrow::int32()), "[[1,2,3], [4,5], [6,7], [8,9,10,11]]", &list_array);

    auto eq_ = arrow::compute::CallFunction("list_flatten", {list_array});
    auto eq_array = eq_->array_as<arrow::Int32Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}