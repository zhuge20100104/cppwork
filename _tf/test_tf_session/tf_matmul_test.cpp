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


TEST(TfMatNulTests, MatMul) {
    // MatMul 测试
    Scope root = Scope::NewRootScope();
    
    auto a = ops::Fill(root, {3, 2}, 1.0f);
    auto b = ops::Fill(root, {2, 3}, 3.0f);
     
    auto mat_mul_ = ops::MatMul(root, a, b);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({a, b, mat_mul_}, &outputs);

    test::PrintTensorValue<float>(std::cout, outputs[0]);
    test::PrintTensorValue<float>(std::cout, outputs[1]);
    test::PrintTensorValue<float>(std::cout, outputs[2]);

    std::vector<float> v_a(6, 1.0f);
    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({v_a.data(), v_a.size()}, {3, 2}));

    std::vector<float> v_b(6, 3.0f);
    test::ExpectTensorEqual<float>(outputs[1], test::AsTensor<float>({v_b.data(), v_b.size()}, {2, 3}));
       
    std::vector<float> v_mat_mul(9, 6.0f);
    test::ExpectTensorEqual<float>(outputs[2], test::AsTensor<float>({v_mat_mul.data(), v_mat_mul.size()}, {3, 3}));
}