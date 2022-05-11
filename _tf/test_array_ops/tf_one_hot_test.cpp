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


TEST(TfArrayOpsTests, OneHot1) {
    // 转换为 one-hot向量
    // Refers to https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/one-hot
    Scope root = Scope::NewRootScope();
    auto indices = test::AsTensor<int>({0, 2, -1, 1}, {4});
    auto onehot_ops = ops::OneHot(root, indices, 3, 5.0f, 0.0f);
   
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({onehot_ops.output}, &outputs);

    std::cout << outputs[0].DebugString() << "\n";

    test::PrintTensorValue<float>(std::cout, outputs[0], 4);

    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({
    5.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 5.0f,  // one_hot(2)
    0.0f, 0.0f, 0.0f,  // one_hot(-1)
    0.0f, 5.0f, 0.0f
    }, {4, 3}));
}

TEST(TfArrayOpsTests, OneHot2) {
    // 转换为 one-hot向量 axis=0，纵轴方向上的onehot
    // Refers to https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/one-hot
    Scope root = Scope::NewRootScope();
    auto indices = test::AsTensor<int>({0, 2, -1, 1}, {4});
    auto attrs = ops::OneHot::Axis(0);
    auto onehot_ops = ops::OneHot(root, indices, 3, 0.0f, 3.0f, attrs);
   
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({onehot_ops.output}, &outputs);

    std::cout << outputs[0].DebugString() << "\n";

    test::PrintTensorValue<float>(std::cout, outputs[0], 4);

    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({
    0.0f, 3.0f, 3.0f, 3.0f,
    3.0f, 3.0f,	3.0f, 0.0f,
    3.0f, 0.0f, 3.0f, 3.0f
    }, {3, 4}));
}

TEST(TfArrayOpsTests, OneHot3) {
    // 转换为 one-hot向量，多行多列
    // Refers to https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/one-hot
    Scope root = Scope::NewRootScope();
    auto indices = test::AsTensor<int>({0, 2, 1, -1}, {2, 2});
    auto onehot_ops = ops::OneHot(root, indices, 3, 1.0f, 0.0f);
   
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({onehot_ops.output}, &outputs);

    std::cout << outputs[0].DebugString() << "\n";

    test::PrintTensorValue<float>(std::cout, outputs[0], 3);

    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({
    1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f,  // one_hot(2)
    0.0f, 1.0f, 0.0f,  // one_hot(1)
    0.0f, 0.0f, 0.0f   // one_hot(-1)
    }, {2, 2, 3}));
}


