#include <string>
#include <vector>
#include <glog/logging.h>
#include "death_handler/death_handler.h"
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

TEST(TfCastReduceTests, ReduceMean) {
    // ReduceMin 测试
    Scope root = Scope::NewRootScope();

    ClientSession session(root);
    std::vector<Tensor> outputs;

    auto c = ops::Const(root,  {{1, 2, 3}, {2, 2, 3}});
    auto mean_ = ops::Mean(root, c, {0});

    // 对第0维，纵向求平均值
    session.Run({mean_}, &outputs);
    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({1, 2, 3}, {3})); 
}

TEST(TfCastReduceTests, ReduceSum) {
    // ReduceSum 测试
    Scope root = Scope::NewRootScope();
    ClientSession session(root);
    std::vector<Tensor> outputs;

    auto c = ops::Const(root,  {{1, 2, 3}, {2, 2, 3}});
    auto sum_ = ops::Sum(root, c, {1});

    // 对第1维，横向求和
    session.Run({sum_}, &outputs);
    
    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({6, 7}, {2})); 
}
