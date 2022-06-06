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

TEST(TfArrayOpsTests, FakeQuantWithMinMaxArgsDemo) {
    // Fake-quantize the 'inputs' tensor, type float to 'outputs' tensor of same type.
    // Refers to https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/fake-quant-with-min-max-args
    // Refers to https://zhuanlan.zhihu.com/p/79744430
    Scope root = Scope::NewRootScope();
    
    auto input = test::AsTensor<float>({3.1415926f, 6.2831852f, 3.1415926f, 6.2831852f}, {2, 2});
   
    auto fake_quant_ops = ops::FakeQuantWithMinMaxArgs(root, input);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({fake_quant_ops.outputs}, &outputs);

    std::cout << outputs[0].DebugString() << "\n";

    test::PrintTensorValue<float>(std::cout, outputs[0]);
    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({3.152941226959228516, 5.976470470428466797, 3.152941226959228516, 5.976470470428466797}, {2, 2}));
}