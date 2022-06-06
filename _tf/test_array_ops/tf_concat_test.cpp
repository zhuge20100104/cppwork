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

TEST(TfArrayOpsTests, Concat1) {
    // 对一维或者单一标量做广播扩张，方便张量计算，会占据一个新的内存节点
    // Refers to https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/broadcast-to
    Scope root = Scope::NewRootScope();
    auto input_tensor1 = test::AsTensor<float>({1.0f}, {});
    auto input_tensor2 = test::AsTensor<float>({2.0f}, {});
    auto concat_op = ops::Concat(root, {input_tensor1, input_tensor2}, {0});
   
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({concat_op}, &outputs);
    test::PrintTensorValue<float>(std::cout, outputs[0]);
    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({1.0f, 2.0f}, {2}));
}


TEST(TfArrayOpsTests, Concat2) {
    // 对一维或者单一标量做广播扩张，方便张量计算，会占据一个新的内存节点
    // Refers to https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/broadcast-to
    Scope root = Scope::NewRootScope();
    auto input_tensor1 = test::AsTensor<float>({1.0f, 2.0f, 3.0f, 4.0f}, {2, 2});
    auto input_tensor2 = test::AsTensor<float>({5.0f, 6.0f, 7.0f, 8.0f}, {2, 2});
    auto concat_op = ops::Concat(root, {input_tensor1, input_tensor2}, {0});
   
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({concat_op}, &outputs);
    test::PrintTensorValue<float>(std::cout, outputs[0]);
    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f}, {4, 2}));
}

TEST(TfArrayOpsTests, Concat3) {
    // 对一维或者单一标量做广播扩张，方便张量计算，会占据一个新的内存节点
    // Refers to https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/broadcast-to
    Scope root = Scope::NewRootScope();
    auto input_tensor1 = test::AsTensor<float>({1.0f, 2.0f, 3.0f, 4.0f}, {2, 2});
    auto input_tensor2 = test::AsTensor<float>({5.0f, 6.0f, 7.0f, 8.0f}, {2, 2});
    auto concat_op = ops::Concat(root, {input_tensor1, input_tensor2}, {1});
   
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({concat_op}, &outputs);
    test::PrintTensorValue<float>(std::cout, outputs[0]);
    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({1.0f, 2.0f, 5.0f, 6.0f, 3.0f, 4.0f, 7.0f, 8.0f}, {2, 4}));
}