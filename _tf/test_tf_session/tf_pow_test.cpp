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


TEST(TfPowTests, PowSquareSqrt) {
    // Pow/Square/Sqrt 测试
    Scope root = Scope::NewRootScope();
    
    auto a = ops::Fill(root, {1, 2}, 3.0f);
    auto pow_ = ops::Pow(root, a, {3.0f});
    auto square_ = ops::Square(root, a);
    auto sqrt_ = ops::Sqrt(root, a);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({a, pow_, square_, sqrt_}, &outputs);

    test::PrintTensorValue<float>(std::cout, outputs[0]);
    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({3.0, 3.0}, {1, 2}));

    test::PrintTensorValue<float>(std::cout, outputs[1]);
    test::ExpectTensorEqual<float>(outputs[1], test::AsTensor<float>({27.0, 27.0}, {1, 2}));

    test::PrintTensorValue<float>(std::cout, outputs[2]);
    test::ExpectTensorEqual<float>(outputs[2], test::AsTensor<float>({9.0, 9.0}, {1, 2}));

    test::PrintTensorValue<float>(std::cout, outputs[3]);
    test::ExpectTensorEqual<float>(outputs[3], test::AsTensor<float>({1.732050776481628418, 1.732050776481628418}, {1, 2}));
}
