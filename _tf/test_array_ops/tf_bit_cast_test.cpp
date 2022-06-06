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

TEST(TfArrayOpsTests, Bitcast1) {
    // 对底层buffer做强制类型转换，
    // Refers to https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/bitcast
    Scope root = Scope::NewRootScope();
    auto input_tensor = test::AsTensor<uint32_t>({0xffffffff}, {});
    auto bit_cast_op = ops::Bitcast(root, input_tensor, DT_UINT8);
   
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({bit_cast_op }, &outputs);

    test::ExpectTensorEqual<uint8_t>(outputs[0], test::AsTensor<uint8_t>({255, 255, 255, 255}, {4}));
}

TEST(TfArrayOpsTests, Bitcast2) {
    // 对底层buffer做强制类型转换，
    // Refers to https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/bitcast
    Scope root = Scope::NewRootScope();
    auto tensor1 = test::AsTensor<float>({1.0f, 2.0f, 3.0f}, {3});
    auto tensor2 = test::AsTensor<float>({0.0f, 2.0f, 3.0f}, {3});
    auto equality = ops::Equal(root, tensor1, tensor2);
    auto equality_cast = ops::Cast(root, equality, DT_FLOAT);
    auto equality_bitcast = ops::Bitcast(root, equality_cast, DT_UINT8);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({equality, equality_cast, equality_bitcast}, &outputs);

    test::ExpectTensorEqual<bool>(outputs[0], test::AsTensor<bool>({false, true, true}, {3}));

    test::ExpectTensorEqual<float>(outputs[1], test::AsTensor<float>({0.0f, 1.0f, 1.0f}, {3}));

    test::ExpectTensorEqual<uint8_t>(outputs[2], test::AsTensor<uint8_t>({0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 128, 63}, {3, 4}));
}


