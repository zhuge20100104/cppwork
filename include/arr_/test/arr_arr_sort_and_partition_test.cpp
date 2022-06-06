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

GTEST_TEST(ArrSortAndPartitionTests, PartitionNthIndexies) {
    // 打印 个元素排序后的索引位置， 例如
    // 此处打印 1 0 4 3 2
    std::shared_ptr<arrow::Array> values1;
    arrow::ipc::internal::json::ArrayFromJSON(arrow::int32(), R"([2,1,6, 5,4])", &values1);
    
   
    arrow::compute::PartitionNthOptions options{2};
    auto eq_ = arrow::compute::CallFunction("partition_nth_indices", {values1}, &options);
   
    auto eq_array = eq_->array_as<arrow::UInt64Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrSortAndPartitionTests, ArraySortIndcies) {
    //  打印 个元素排序后的索引位置， 例如
    // 此处打印 1 0 4 3 2
    std::shared_ptr<arrow::Array> values1;
    arrow::ipc::internal::json::ArrayFromJSON(arrow::int32(), R"([2,1,6, 5,4])", &values1);
    
   
    arrow::compute::ArraySortOptions options{arrow::compute::SortOrder::Ascending};
    auto eq_ = arrow::compute::CallFunction("array_sort_indices", {values1}, &options);
   
    auto eq_array = eq_->array_as<arrow::UInt64Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

