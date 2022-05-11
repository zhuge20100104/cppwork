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


TEST(TfArthimaticTests, Add) {
    // Add 测试
    Scope root = Scope::NewRootScope();
 
    auto a = ops::Fill(root, {1, 3}, 3);
    auto b = ops::OnesLike(root, a);
    auto add = ops::Add(root, a, b);
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({add}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({4, 4, 4}, {1, 3}));
}

TEST(TfArthimaticTests, Sub) {
    // Sub 测试
    Scope root = Scope::NewRootScope();
    
    auto a = ops::Fill(root, {1, 3}, 3);
    auto b = ops::OnesLike(root, a);
    auto sub_ = ops::Sub(root, a, b);
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({sub_}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({2, 2, 2}, {1, 3}));
}

TEST(TfArthimaticTests, Mul) {
    // Mul 测试
    Scope root = Scope::NewRootScope();
    
    auto a = ops::Fill(root, {1, 3}, 3);
    auto b = ops::OnesLike(root, a);
    auto mul_ = ops::Multiply(root, a, b);
    ClientSession session(root);
    std::vector<Tensor> outputs;
    
    session.Run({mul_}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({3, 3, 3}, {1, 3}));
}

TEST(TfArthimaticTests, Div) {
    // Div 测试
    Scope root = Scope::NewRootScope();
    
    auto a = ops::Fill(root, {1, 3}, 3);
    auto b = ops::OnesLike(root, a);
    auto div_ = ops::Div(root, a, b);
    ClientSession session(root);
    std::vector<Tensor> outputs;
    
    session.Run({div_}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({3, 3, 3}, {1, 3}));
}