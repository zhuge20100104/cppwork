#include <string>
#include <vector>
#include <algorithm>
#include <glog/logging.h>
#include "death_handler/death_handler.h"
#include "arr_/arr_.h"
#include "img_util/img_util.h"
#include "tf_/tensor_testutil.h"
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/cc/training/coordinator.h"
#include "tensorflow/core/framework/graph.pb.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/framework/types.pb.h"
#include "tensorflow/core/lib/core/notification.h"
#include "tensorflow/core/lib/core/status_test_util.h"
#include "tensorflow/core/platform/env.h"
#include "tensorflow/core/platform/test.h"
#include "tensorflow/core/protobuf/error_codes.pb.h"
#include "tensorflow/core/protobuf/queue_runner.pb.h"
#include "tensorflow/core/public/session.h"


using namespace tensorflow;

int main(int argc, char** argv) {
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;

    Debug::DeathHandler dh;

    google::InitGoogleLogging("./logs.log");
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

auto SRC_SCHEMA = ::arrow::schema(
    {{arrow::field("a", arrow::boolean())}, {arrow::field("b", arrow::boolean())}});

auto DST_SCHEMA = ::arrow::schema({{arrow::field("a", arrow::boolean())},
                                   {arrow::field("b", arrow::boolean())},
                                   {arrow::field("res", arrow::boolean())}});

std::string const AND_TABLE =  R"([
                                            {"a": true, "b": true},
                                            {"a": true,  "b": true},
                                            {"a": true,  "b": false},
                                            {"a": true,  "b": false},
                                            {"a": false,  "b": false}
                                            ])";

std::string const AND_RES_TABLE =  R"([
                                            {"a": true, "b": true, "res": true},
                                            {"a": true,  "b": true, "res": true},
                                            {"a": true,  "b": false, "res": false},
                                            {"a": true,  "b": false, "res": false},
                                            {"a": false,  "b": false, "res": false}
                                            ])";

TEST(TfArrayOpsTests, ArrowTest) {
    // 两列bool类型与运算
    auto tb = ArrowUtil::TableFromJSON(SRC_SCHEMA, {AND_TABLE});

    auto ds = std::make_shared<arrow::dataset::InMemoryDataset>(tb);
    auto scanner_builder = ds->NewScan().ValueOrDie();
    scanner_builder->Project(
        {arrow::compute::field_ref("a"), arrow::compute::field_ref("b"),
         arrow::compute::call("and", {arrow::compute::field_ref("a"),
                                            arrow::compute::field_ref("b")})},
        {"a", "b", "res"});
    auto scanner = scanner_builder->Finish().ValueOrDie();
    auto proj_tb = scanner->ToTable().ValueOrDie();
    auto tb_res = ArrowUtil::TableFromJSON(DST_SCHEMA, {AND_RES_TABLE});
    arrow::PrettyPrint(*proj_tb, {}, &std::cerr);
    ArrowUtil::AssertTablesEqual(*tb_res, *proj_tb, true, true);
}


GTEST_TEST(TfArrayOpsTests, CompareEqual) {
    const std::string src_img = "../images/src.png";
    const std::string dst_img = "../images/dst.png";
    bool is_equal = ImageUtil::compare_equal(src_img, dst_img);
    ASSERT_TRUE(is_equal);
}

GTEST_TEST(TfArrayOpsTests, CompareNotEqual) {
    const std::string src_img = "../images/src.png";
    const std::string dst_img = "../images/dst2.png";
    bool is_equal = ImageUtil::compare_equal(src_img, dst_img);
    ASSERT_FALSE(is_equal);
}

GTEST_TEST(TfArrayOpsTests, CompareSizeNotEqual) {
    const std::string src_img = "../images/src.png";
    const std::string dst_img = "../images/dst3.png";
    bool is_equal = ImageUtil::compare_equal(src_img, dst_img);
    ASSERT_FALSE(is_equal);
}

GTEST_TEST(TfArrayOpsTests, TestMaxElement) {
    std::vector<float> eles {0.1, 0.2, 0.3, 0.3, 0.2, 0.4, 0.6, 0.5, 0.3};
    auto index0 = std::max_element(eles.begin(), eles.begin()+3)-eles.begin();
    auto index1 = std::max_element(eles.begin()+3, eles.begin()+6)-(eles.begin()+3);
    auto index2 = std::max_element(eles.begin()+6, eles.begin()+9)-(eles.begin()+6);
    std::cerr << index0 << "\n";
    std::cerr << index1 << "\n";
    std::cerr << index2 << "\n";
}

