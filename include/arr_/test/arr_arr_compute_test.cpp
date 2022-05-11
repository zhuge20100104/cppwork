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

GTEST_TEST(ArrComputeTests, ComputeGreater) { 
    // 比较两列 int 值中 int1 > int2的值， greater函数
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);
    auto array_a = tb_.GetColumnByName("int1");
    auto array_b = tb_.GetColumnByName("int2");
    
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);
    auto array_b_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_b);

    auto compared_datum = arrow::compute::CallFunction("greater", {array_a_res, array_b_res});
    auto array_a_gt_b_compute = compared_datum->make_array();
    
    arrow::PrettyPrint(*array_a_gt_b_compute, {}, &std::cerr);

    auto schema =
      arrow::schema({arrow::field("int1", arrow::int64()), arrow::field("int2", arrow::int64()),
                     arrow::field("a>b? (arrow)", arrow::boolean())});
    
    std::shared_ptr<arrow::Table> my_table = arrow::Table::Make(
      schema, {array_a_res, array_b_res, array_a_gt_b_compute}, tb_.num_rows());
    
    arrow::PrettyPrint(*my_table, {}, &std::cerr);
}

GTEST_TEST(ArrComputeTests, ComputeMinMax) {
    // 计算int1列的最大值和最小值
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    arrow::compute::ScalarAggregateOptions scalar_aggregate_options;
    scalar_aggregate_options.skip_nulls = false;

    auto min_max = arrow::compute::CallFunction("min_max", {array_a_res}, &scalar_aggregate_options);

    // Unpack struct scalar result (a two-field {"min", "max"} scalar)
    auto min_value = min_max->scalar_as<arrow::StructScalar>().value[0];
    auto max_value = min_max->scalar_as<arrow::StructScalar>().value[1];

    ASSERT_EQ(min_value->ToString(), "1");
    ASSERT_EQ(max_value->ToString(), "8");
} 

GTEST_TEST(ArrComputeTests, ComputeMean) {
    // 计算int1列的平均值
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    arrow::compute::ScalarAggregateOptions scalar_aggregate_options;
    scalar_aggregate_options.skip_nulls = false;

    auto mean= arrow::compute::CallFunction("mean", {array_a_res}, &scalar_aggregate_options);

    auto const& mean_value = mean->scalar_as<arrow::Scalar>();
    
    ASSERT_EQ(mean_value.ToString(), "4.5");
} 

GTEST_TEST(ArrComputeTests, ComputeAdd) {
    // 将第一列的值加3
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);

    std::shared_ptr<arrow::Scalar> increment = std::make_shared<arrow::Int64Scalar>(3);

    auto add = arrow::compute::CallFunction("add", {array_a_res, increment});
    std::shared_ptr<arrow::Array> incremented_array = add->array_as<arrow::Array>();
    arrow::PrettyPrint(*incremented_array, {}, &std::cerr);
} 


GTEST_TEST(ArrComputeTests, ComputeAddArray) {
    // int1和int2两列相加
    char const* json_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);
    auto array_a = tb_.GetColumnByName("int1");
    auto array_a_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_a);
    
    auto array_b = tb_.GetColumnByName("int2");
    auto array_b_res = ArrowUtil::chunked_array_to_array<int64_t, numbuildT<arrow::Int64Type>, arrow::Int64Array>(array_b);

    auto add = arrow::compute::CallFunction("add", {array_a_res, array_b_res});
    std::shared_ptr<arrow::Array> incremented_array = add->array_as<arrow::Array>();
    arrow::PrettyPrint(*incremented_array, {}, &std::cerr);
} 

GTEST_TEST(ArrComputeTests, ComputeStringEqual) {
    // 比较s1和s2两列是否相等
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    auto array_b = tb_.GetColumnByName("s2");
    auto array_b_res = ArrowUtil::chunked_array_to_str_array(array_b);

    auto eq_ = arrow::compute::CallFunction("equal", {array_a_res, array_b_res});
    std::shared_ptr<arrow::Array> eq_array = eq_->array_as<arrow::Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrComputeTests, ComputeCustom) {
    // 自己写算法逐个比较相等 
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);
    auto arr1 = tb_.GetColumnByName("s1");
    auto arr2 = tb_.GetColumnByName("s2");
    auto v1 = ArrowUtil::chunked_array_to_str_vector(arr1);
    auto v2 = ArrowUtil::chunked_array_to_str_vector(arr2);
    for(std::size_t i=0; i<v1.size(); ++i) {
        if(v1[i] != v2[i]) {
            std::cerr << v1[i] << "!=" << v2[i] << "\n";
        }
    }
}

GTEST_TEST(ArrComputeTests, ComputeCustomDbl) { 
    // 自己写算法比较double值
    char const* json_path = "../data/custom_dbl.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);
    auto arr1 = tb_.GetColumnByName("dbl1");
    auto arr2 = tb_.GetColumnByName("dbl2");
    auto v1 = ArrowUtil::chunked_array_to_vector<double, arrow::DoubleArray>(arr1);
    auto v2 = ArrowUtil::chunked_array_to_vector<double, arrow::DoubleArray>(arr2);
    for(std::size_t i=0; i<v1.size(); ++i) {
        if(v1[i] != v2[i]) {
            std::cerr << v1[i] << "!=" << v2[i] << "\n";
        }
    }
}

GTEST_TEST(ArrComputeTests, ComputeEqualDbl) { 
    // 使用equal函数比较double值
    char const* json_path = "../data/custom_dbl.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);
    auto arr1 = tb_.GetColumnByName("dbl1");
    auto arr2 = tb_.GetColumnByName("dbl2");

    auto dbl_arr1 = ArrowUtil::chunked_array_to_array<double, numbuildT<arrow::DoubleType>, arrow::DoubleArray>(arr1);
    auto dbl_arr2 = ArrowUtil::chunked_array_to_array<double, numbuildT<arrow::DoubleType>, arrow::DoubleArray>(arr2);

    auto eq_ = arrow::compute::CallFunction("equal", {dbl_arr1, dbl_arr2});
    std::shared_ptr<arrow::Array> eq_array = eq_->array_as<arrow::Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}

GTEST_TEST(ArrComputeTests, StrStartsWith) {
    // 计算s1列以是否以 Zha开头的值
    char const* json_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);

    auto array_a = tb_.GetColumnByName("s1");
    auto array_a_res = ArrowUtil::chunked_array_to_str_array(array_a);

    arrow::compute::MatchSubstringOptions options("Zha");

    auto eq_ = arrow::compute::CallFunction("starts_with", {array_a_res}, &options);
    std::shared_ptr<arrow::Array> eq_array = eq_->array_as<arrow::Array>();
    arrow::PrettyPrint(*eq_array, {}, &std::cerr);
}


