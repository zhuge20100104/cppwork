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

TEST(TfCastReduceTests, Cast) {
    // Cast 测试
    Scope root = Scope::NewRootScope();
    
    auto c_float = ops::Const(root, {1.0, 2.0, 3.0});
    auto c_int = ops::Cast(root, c_float, DT_INT32);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({c_int}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({1, 2, 3}, {3}));  
}

TEST(TfCastReduceTests, ReduceMin) {
    // ReduceMin 测试
    Scope root = Scope::NewRootScope();

    auto c = ops::Const(root, {1, 2, 3});
    auto min_op = ops::Min(root, c, {0});

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({min_op}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({1}, {})); 
}

TEST(TfCastReduceTests, ReduceCastMax) {
    // Cast ReduceMax测试
    Scope root = Scope::NewRootScope();
    
    auto c_dbl = ops::Const(root, {1.0, 2.0, 3.0});
    auto c = ops::Cast(root, c_dbl, DT_INT32);

    auto max_op = ops::Max(root, c, {0});
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({max_op}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({3}, {})); 
}
