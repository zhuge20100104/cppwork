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

TEST(TfArrayOpsTests, Batch2SpaceND1) {
    // 将batch张量转换为N维空间张量
    // Refers to https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/batch-to-space-n-d

    Scope root = Scope::NewRootScope();
    auto input_tensor = test::AsTensor<int>({1, 2, 3, 4}, {4, 1, 1, 1});
    auto block_shape = ops::Const(root, {2, 2});
    auto crops_ = ops::Const(root, {{0,0}, {0, 0}});
    auto batch_2_space_op = ops::BatchToSpaceND(root, input_tensor, block_shape, crops_);
   
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({batch_2_space_op}, &outputs);
    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({1, 2, 3, 4}, {1, 2, 2, 1}));
}


TEST(TfArrayOpsTests, Batch2SpaceND2) {
    // 将batch张量转换为N维空间张量
    // Refers to https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/batch-to-space-n-d

    Scope root = Scope::NewRootScope();
    auto input_tensor = test::AsTensor<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, {4, 1, 1, 3});
    auto block_shape = ops::Const(root, {2, 2});
    auto crops_ = ops::Const(root, {{0,0}, {0, 0}});
    auto batch_2_space_op = ops::BatchToSpaceND(root, input_tensor, block_shape, crops_);
   
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({batch_2_space_op}, &outputs);
    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, {1, 2, 2, 3}));
}


TEST(TfArrayOpsTests, Batch2SpaceND3) {
    // 将batch张量转换为N维空间张量
    // Refers to https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/batch-to-space-n-d

    Scope root = Scope::NewRootScope();
    auto input_tensor = test::AsTensor<int>({1, 3, 9, 11, 2, 4, 10, 12, 5, 7, 13, 15, 6, 8, 14, 16}, {4, 2, 2, 1});
    auto block_shape = ops::Const(root, {2, 2});
    auto crops_ = ops::Const(root, {{0,0}, {0, 0}});
    auto batch_2_space_op = ops::BatchToSpaceND(root, input_tensor, block_shape, crops_);
   
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({batch_2_space_op}, &outputs);
    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}, {1, 4, 4, 1}));
}

TEST(TfArrayOpsTests, Batch2SpaceND4) {
    // 将batch张量转换为N维空间张量
    // Refers to https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/batch-to-space-n-d

    Scope root = Scope::NewRootScope();
    auto input_tensor = test::AsTensor<int>({0, 1, 3, 0, 9, 11, 0, 2, 4, 0, 10, 12, 0, 5, 7, 0, 13, 15, 0, 6, 8, 0, 14, 16}, {8, 1, 3, 1});
    auto block_shape = ops::Const(root, {2, 2});
    auto crops_ = ops::Const(root, {{0,0}, {2, 0}});
    auto batch_2_space_op = ops::BatchToSpaceND(root, input_tensor, block_shape, crops_);
   
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({batch_2_space_op}, &outputs);
    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}, {2, 2, 4, 1}));
}
