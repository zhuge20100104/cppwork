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

TEST(TfArrayOpsTests, Deepcopy) {
    // 深拷贝API
    // Refers to https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/deep-copy
    Scope root = Scope::NewRootScope();
    auto input_tensor = test::AsTensor<int>({1, 2, 3}, {3});
    auto deep_copy_op = ops::DeepCopy(root, input_tensor);
   
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({deep_copy_op}, &outputs);
    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({1, 2, 3}, {3}));

    ASSERT_TRUE(input_tensor.data() != outputs[0].data());
}