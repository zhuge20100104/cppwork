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

GTEST_TEST(ExecEngineTests, ProjectSourceSink) { 
    // 直接Sink原有数据
    char const* csv_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(csv_path, tb);

    auto plan = arrow::compute::ExecPlan::Make().ValueOrDie();
    auto batche_sh = ArrowUtil::MakeBatchAndSchema(tb);

    auto source = ArrowUtil::MakeTestSourceNode(plan.get(), "source",
                                                           batche_sh, true, false).ValueOrDie();

    auto sink_gen = arrow::compute::MakeSinkNode(source, "sink");
    auto res_ex_batches = ArrowUtil::StartAndCollect(plan.get(), sink_gen).result().ValueOrDie();
    
    std::vector<std::shared_ptr<arrow::RecordBatch>> rec_batches;
    ArrowUtil::ConvertExecBatchToRecBatch(tb->schema(), res_ex_batches, rec_batches);

    auto res_tb = arrow::Table::FromRecordBatches(rec_batches).ValueOrDie();
    arrow::PrettyPrint(*res_tb, {}, &std::cerr);
}

GTEST_TEST(ExecEngineTests, ProjectFilterThenProject) { 
    // 先做 Filter > 3的，再做加和
    char const* csv_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(csv_path, tb);

    auto plan = arrow::compute::ExecPlan::Make().ValueOrDie();
    auto batche_sh = ArrowUtil::MakeBatchAndSchema(tb);

    auto source = ArrowUtil::MakeTestSourceNode(plan.get(), "source",
                                                           batche_sh, true, false).ValueOrDie();

    auto predicate = arrow::compute::greater(arrow::compute::field_ref("int1"), arrow::compute::literal(3)).Bind(*batche_sh.schema).ValueOrDie();

    auto filter = arrow::compute::MakeFilterNode(source, "filter", predicate).ValueOrDie();

    std::vector<arrow::compute::Expression> exprs{
        arrow::compute::field_ref("int1"),
        arrow::compute::field_ref("int2"),
        arrow::compute::call("add", { arrow::compute::field_ref("int1"),  arrow::compute::field_ref("int2")}),
    };

    for (auto& expr : exprs) {
        expr = expr.Bind(*batche_sh.schema).ValueOrDie();
    }

    auto projection = arrow::compute::MakeProjectNode(filter, "project", exprs, {"int1", "int2", "add_res"}).ValueOrDie();
    auto sink_gen = arrow::compute::MakeSinkNode(projection, "sink");
    auto res_ex_batches = ArrowUtil::StartAndCollect(plan.get(), sink_gen).result().ValueOrDie();
    
    auto result_schema = arrow::schema({arrow::field("int1", arrow::int64()),
            arrow::field("int2", arrow::int64()), 
            arrow::field("add_res", arrow::int64())}); 

    std::vector<std::shared_ptr<arrow::RecordBatch>> rec_batches;
    ArrowUtil::ConvertExecBatchToRecBatch(result_schema, res_ex_batches, rec_batches);

    auto res_tb = arrow::Table::FromRecordBatches(rec_batches).ValueOrDie();
    arrow::PrettyPrint(*res_tb, {}, &std::cerr);
}


GTEST_TEST(ExecEngineTests, ProjectDblFilter) { 
    // 先Filter startswith Zha, 再 Filter endswith liu
    char const* csv_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(csv_path, tb);

    auto plan = arrow::compute::ExecPlan::Make().ValueOrDie();
    auto batche_sh = ArrowUtil::MakeBatchAndSchema(tb);

    auto source = ArrowUtil::MakeTestSourceNode(plan.get(), "source",
                                                           batche_sh, true, false).ValueOrDie();
    arrow::compute::MatchSubstringOptions s_options("Zha");
    auto s_predicate = arrow::compute::call("starts_with", {arrow::compute::field_ref("s1")}, s_options).Bind(*batche_sh.schema).ValueOrDie();
    auto s_filter = arrow::compute::MakeFilterNode(source, "filter", s_predicate).ValueOrDie();

    arrow::compute::MatchSubstringOptions e_options("liu");
    auto e_predicate = arrow::compute::call("ends_with", {arrow::compute::field_ref("s1")}, e_options).Bind(*batche_sh.schema).ValueOrDie();
    auto e_filter = arrow::compute::MakeFilterNode(s_filter, "filter", e_predicate).ValueOrDie();

    auto sink_gen = arrow::compute::MakeSinkNode(e_filter, "sink");

    auto res_ex_batches = ArrowUtil::StartAndCollect(plan.get(), sink_gen).result().ValueOrDie();
    std::vector<std::shared_ptr<arrow::RecordBatch>> rec_batches;
    ArrowUtil::ConvertExecBatchToRecBatch(tb->schema(), res_ex_batches, rec_batches);

    auto res_tb = arrow::Table::FromRecordBatches(rec_batches).ValueOrDie();
    arrow::PrettyPrint(*res_tb, {}, &std::cerr);
}


GTEST_TEST(ExecEngineTests, ProjectStrEq) { 
    // 比较两列字符串是否相等
    char const* csv_path = "../data/comp_s_eq.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(csv_path, tb);

    auto plan = arrow::compute::ExecPlan::Make().ValueOrDie();
    auto batche_sh = ArrowUtil::MakeBatchAndSchema(tb);

    auto source = ArrowUtil::MakeTestSourceNode(plan.get(), "source",
                                                           batche_sh, true, false).ValueOrDie();

   
    std::vector<arrow::compute::Expression> exprs{
        arrow::compute::field_ref("s1"),
        arrow::compute::field_ref("s2"),
        arrow::compute::call("equal", {arrow::compute::field_ref("s1"),  arrow::compute::field_ref("s2")}),
    };

    for (auto& expr : exprs) {
        expr = expr.Bind(*batche_sh.schema).ValueOrDie();
    }

    auto projection = arrow::compute::MakeProjectNode(source, "project", exprs, {"s1", "s2", "is_equal"}).ValueOrDie();

    auto sink_gen = arrow::compute::MakeSinkNode(projection, "sink");
    auto res_ex_batches = ArrowUtil::StartAndCollect(plan.get(), sink_gen).result().ValueOrDie();
    
    auto result_schema = arrow::schema({arrow::field("s1", arrow::utf8()),
            arrow::field("s2", arrow::utf8()), 
            arrow::field("is_equal", arrow::boolean())}); 

    std::vector<std::shared_ptr<arrow::RecordBatch>> rec_batches;
    ArrowUtil::ConvertExecBatchToRecBatch(result_schema, res_ex_batches, rec_batches);

    auto res_tb = arrow::Table::FromRecordBatches(rec_batches).ValueOrDie();
    arrow::PrettyPrint(*res_tb, {}, &std::cerr);
}


GTEST_TEST(ExecEngineTests, ProjectIfElseMultiple) { 
    // 如果第一列 int1=3，替换成300
    // 如果第一列 int1=4，替换成400
    // 如果第一列 int1=5, 替换成500
    // 否则保持第一列值
    // 使用纯if_else算子实现case_when的效果
    // 目前case_when算子没有调通
    char const* csv_path = "../data/comp_gt.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(csv_path, tb);

    // Source Node
    auto plan = arrow::compute::ExecPlan::Make().ValueOrDie();
    auto batche_sh = ArrowUtil::MakeBatchAndSchema(tb);

    auto source = ArrowUtil::MakeTestSourceNode(plan.get(), "source",
                                                           batche_sh, true, false).ValueOrDie();

    // Three Node
    std::vector<arrow::compute::Expression> exprs{
        arrow::compute::field_ref("int1"),
        arrow::compute::field_ref("int2"),
        arrow::compute::call("if_else", {
            arrow::compute::call("equal", {arrow::compute::field_ref("int1"),arrow::compute::literal(3)}), 
            arrow::compute::literal(300),
            arrow::compute::field_ref("int1")
        })
    };

    for (auto& expr : exprs) {
        expr = expr.Bind(*batche_sh.schema).ValueOrDie();
    }
    auto three_node = arrow::compute::MakeProjectNode(source, "project", exprs, {"int1", "int2", "int3"}).ValueOrDie();

    // 构建Schema
    auto result_schema = arrow::schema({arrow::field("int1", arrow::int64()),
            arrow::field("int2", arrow::int64()), 
            arrow::field("int3", arrow::int64())}); 

    // four_node
    exprs.clear();
    exprs = {
        arrow::compute::field_ref("int1"),
        arrow::compute::field_ref("int2"),
        arrow::compute::call("if_else", {
            arrow::compute::call("equal", {arrow::compute::field_ref("int1"),arrow::compute::literal(4)}), 
            arrow::compute::literal(400),
            arrow::compute::field_ref("int3")
        })
    };

    for (auto& expr : exprs) {
        expr = expr.Bind(*result_schema).ValueOrDie();
    }

    auto four_node = arrow::compute::MakeProjectNode(three_node, "project", exprs, {"int1", "int2", "int3"}).ValueOrDie();

    // five node
    exprs.clear();
    exprs = {
        arrow::compute::field_ref("int1"),
        arrow::compute::field_ref("int2"),
        arrow::compute::call("if_else", {
            arrow::compute::call("equal", {arrow::compute::field_ref("int1"),arrow::compute::literal(5)}), 
            arrow::compute::literal(500),
            arrow::compute::field_ref("int3")
        })
    };

    for (auto& expr : exprs) {
        expr = expr.Bind(*result_schema).ValueOrDie();
    }

    auto five_node = arrow::compute::MakeProjectNode(four_node, "project", exprs, {"int1", "int2", "int3"}).ValueOrDie();


    auto sink_gen = arrow::compute::MakeSinkNode(five_node, "sink");
    
    auto res_ex_batches = ArrowUtil::StartAndCollect(plan.get(), sink_gen).result().ValueOrDie();
    
    std::vector<std::shared_ptr<arrow::RecordBatch>> rec_batches;
    ArrowUtil::ConvertExecBatchToRecBatch(result_schema, res_ex_batches, rec_batches);

    auto res_tb = arrow::Table::FromRecordBatches(rec_batches).ValueOrDie();
    arrow::PrettyPrint(*res_tb, {}, &std::cerr);
}