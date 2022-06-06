#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <glog/logging.h>
#include "tensorflow/core/platform/test.h"
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
#include "tf_/queue_runner.h"


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

TEST(TfArrayOpsTests, InplaceAdd) {
    // Adds v into specified rows of x.
    // Refers https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/inplace-add
    Scope root = Scope::NewRootScope();
    
    // 将3，3添加到第一行
    auto tensor_ = test::AsTensor<int>({1, 2, 1, 2}, {2,2});
    auto indexes = test::AsTensor<int>({1}, {1});
    auto added_values = test::AsTensor<int>({3, 3}, {1, 2});

    auto iadd_ops = ops::InplaceAdd(root, tensor_, indexes, added_values);
   
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({iadd_ops.y}, &outputs);

    std::cout << outputs[0].DebugString() << "\n";

    test::PrintTensorValue<int>(std::cout, outputs[0]);
    
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({1, 2, 4, 5}, {2, 2}));
}
