#include "arr_/arr_.h"
#include <memory>
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


GTEST_TEST(DatasetTests, ProjectGreater) { 
    // 两列比较判断
    char const* csv_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(csv_path, tb);

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project({
        arrow::compute::field_ref("int1"),
        arrow::compute::field_ref("int2"),
        arrow::compute::call("greater", {arrow::compute::field_ref("int1"), arrow::compute::field_ref("int2")})
    }, {"int1", "int2", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}

GTEST_TEST(DatasetTests, ProjectAddLiteral) { 
    // 本列加一个标量
    char const* csv_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(csv_path, tb);

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    scanner_builder->Project({
        arrow::compute::field_ref("int1"),
        arrow::compute::field_ref("int2"),
        arrow::compute::call("add", {arrow::compute::field_ref("int1"), arrow::compute::literal(3)})
    }, {"int1", "int2", "added_res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}

GTEST_TEST(DatasetTests, ProjectAddColumn) { 
    // 两列相加
    char const* csv_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(csv_path, tb);

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    scanner_builder->Project({
        arrow::compute::field_ref("int1"),
        arrow::compute::field_ref("int2"),
        arrow::compute::call("add", {arrow::compute::field_ref("int1"), arrow::compute::field_ref("int2")})
    }, {"int1", "int2", "added_column_res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}

GTEST_TEST(DatasetTests, ProjectStrEq) { 
    // 两列字符串相等
    char const* csv_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(csv_path, tb);

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    scanner_builder->Project({
        arrow::compute::field_ref("s1"),
        arrow::compute::field_ref("s2"),
        arrow::compute::call("equal", {arrow::compute::field_ref("s1"), arrow::compute::field_ref("s2")})
    }, {"s1", "s2", "is_equal"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}

GTEST_TEST(DatasetTests, ProjectDoubleEq) { 
    // 两列double相等
    char const* csv_path = "../data/custom_dbl.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(csv_path, tb);

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    scanner_builder->Project({
        arrow::compute::field_ref("dbl1"),
        arrow::compute::field_ref("dbl2"),
        arrow::compute::call("equal", {arrow::compute::field_ref("dbl1"), arrow::compute::field_ref("dbl2")})
    }, {"dbl1", "dbl2", "is_dbl_equal"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}

GTEST_TEST(DatasetTests, ProjectStrStartsWith) { 
    // 字符串以Zha开头
    char const* csv_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(csv_path, tb);

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    arrow::compute::MatchSubstringOptions options("Zha");

    scanner_builder->Project({
        arrow::compute::field_ref("s1"),
        arrow::compute::field_ref("s2"),
        arrow::compute::call("starts_with", {arrow::compute::field_ref("s1")}, options)
    }, {"s1", "s2", "is_str_starts_with"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}

GTEST_TEST(DatasetTests, ProjectIntIfElse) { 
    // if-else 如果int1=3，则替换为100，否则使用int1
    char const* csv_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(csv_path, tb);

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    
    scanner_builder->Project({
        arrow::compute::field_ref("int1"),
        arrow::compute::field_ref("int2"),
        arrow::compute::call("if_else", {arrow::compute::call("equal", {arrow::compute::field_ref("int1"),arrow::compute::literal(3)}), arrow::compute::literal(100), arrow::compute::field_ref("int1")
        })
    }, {"int1", "int2", "int1_res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}

GTEST_TEST(DatasetTests, ProjectListValLen) { 
    // 计算list[]列的长度
    char const* js_path = "../data/test_list.json";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_json(js_path, tb);
    arrow::PrettyPrint(*tb, {}, &std::cerr);
    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    scanner_builder->Project({
        arrow::compute::field_ref("ls"),
        arrow::compute::field_ref("int1"),
        arrow::compute::call("list_value_length", {arrow::compute::field_ref("ls")})
    }, {"ls", "int1", "ls_len"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}

GTEST_TEST(DatasetTests, ProjectCast) { 
    // Int类型的int1列，转bool类型
    char const* csv_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(csv_path, tb);
    arrow::PrettyPrint(*tb, {}, &std::cerr);
    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();

    auto options = arrow::compute::CastOptions::Safe(arrow::boolean());

    scanner_builder->Project({
        arrow::compute::field_ref("int1"),
        arrow::compute::field_ref("int2"),
        arrow::compute::call("cast", {arrow::compute::field_ref("int1")}, options)
    }, {"int1", "int2", "int1_bool"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}


GTEST_TEST(DatasetTests, ProjectDayOfWeek) { 
    // 计算某天是一周的第几天
    char const* csv_path = "../data/test.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(csv_path, tb);
    arrow::PrettyPrint(*tb, {}, &std::cerr);
    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    
    arrow::compute::DayOfWeekOptions options(false, 7);
    
    scanner_builder->Project({
        arrow::compute::field_ref("Timestamps"),
        arrow::compute::call("day_of_week", {arrow::compute::field_ref("Timestamps")}, options)
    }, {"Timestamps", "nth_day"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
}
