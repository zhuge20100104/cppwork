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


GTEST_TEST(ArrSelectionTests, CaseWhen) {
    // 多重if-else语句

    std::shared_ptr<arrow::Scalar> cond_true, cond_false;
    
    arrow::ipc::internal::json::ScalarFromJSON(arrow::boolean(), "true", &cond_true);
    
    arrow::ipc::internal::json::ScalarFromJSON(arrow::boolean(), "false", &cond_false);

    std::shared_ptr<arrow::Array> values1, values2;
    arrow::ipc::internal::json::ArrayFromJSON(arrow::int32(), R"([1,2,3,4])", &values1);
    
    arrow::ipc::internal::json::ArrayFromJSON(arrow::int32(), R"([5,6,7,8])", &values2);

    auto cond_res = arrow::compute::CallFunction("make_struct", {cond_false, cond_true});
    auto& cond_final = *cond_res;
    auto eq_ = arrow::compute::CallFunction("case_when", {cond_final, values1, values2});
   
    auto eq_array = eq_->array_as<arrow::Int32Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrSelectionTests, Coalesce) {
    // Coalesce 函数取多组中 第一个不是 null的值
    std::shared_ptr<arrow::Scalar> cond_true, cond_false;
    
    arrow::ipc::internal::json::ScalarFromJSON(arrow::boolean(), "true", &cond_true);
    
    arrow::ipc::internal::json::ScalarFromJSON(arrow::boolean(), "false", &cond_false);

    std::shared_ptr<arrow::Array> values1, values2;
    arrow::ipc::internal::json::ArrayFromJSON(arrow::int32(), R"([null,2,3,4])", &values1);
    
    arrow::ipc::internal::json::ArrayFromJSON(arrow::int32(), R"([5,6,7,8])", &values2);

    auto eq_ = arrow::compute::CallFunction("coalesce", {values1, values2});
   
    auto eq_array = eq_->array_as<arrow::Int32Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


GTEST_TEST(ArrSelectionTests, IfElse) {
    // if_else函数, true取values1， false取values2
    std::shared_ptr<arrow::Scalar> cond_false;    
    arrow::ipc::internal::json::ScalarFromJSON(arrow::boolean(), "false", &cond_false);

    std::shared_ptr<arrow::Array> values1, values2;
    arrow::ipc::internal::json::ArrayFromJSON(arrow::int32(), R"([null,2,3,4])", &values1);
    
    arrow::ipc::internal::json::ArrayFromJSON(arrow::int32(), R"([5,6,7,8])", &values2);

    auto eq_ = arrow::compute::CallFunction("if_else", {cond_false, values1, values2});
   
    auto eq_array = eq_->array_as<arrow::Int32Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}
