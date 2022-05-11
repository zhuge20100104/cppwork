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


TEST(TfArthimaticTests, Abs) {
    // Abs 测试
    Scope root = Scope::NewRootScope();
    auto eles = test::AsTensor<int>({-1, 2, -3, -4}, {4});
    auto abs_op = ops::Abs(root, eles);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({abs_op.y}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({1, 2, 3, 4}, {4}));
}

TEST(TfArthimaticTests, AccumulateNV2) {
    // AccumulateNV2 多个Tensor相加测试
    Scope root = Scope::NewRootScope();
    auto in1 = test::AsTensor<int>({1, 2, 3, 4}, {4});
    auto in2 = test::AsTensor<int>({5, 6, 7, 8}, {4});
    auto accu_op = ops::AccumulateNV2(root, {in1, in2}, {4});

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({accu_op.sum}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({6, 8, 10, 12}, {4}));
}


TEST(TfArthimaticTests, ACos) {
    // ACos Tensor元素 反余弦函数测试
    Scope root = Scope::NewRootScope();
    auto in1 = test::AsTensor<float>({0.5, 0}, {2});
    auto acos_op = ops::Acos(root, {in1});

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({acos_op.y}, &outputs);

    test::PrintTensorValue<float>(std::cout, outputs[0]);
    // pi/3, pi/2
    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({1.047197580337524414, 1.570796370506286621}, {1, 2}));
}


TEST(TfArthimaticTests, Add) {
    // Add Tensor元素 两个Tensor相加测试
    Scope root = Scope::NewRootScope();
    auto in1 = test::AsTensor<int>({1, 1}, {2});
    auto in2 = test::AsTensor<int>({2, 2}, {2});
    auto add_op = ops::Add(root, in1, in2);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({add_op.z}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);

    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({3, 3}, {2}));
}


TEST(TfArthimaticTests, AddN) {
    // AddN Tensor元素 N个Tensor相加测试
    Scope root = Scope::NewRootScope();
    auto in1 = test::AsTensor<int>({1, 1}, {2});
    auto in2 = test::AsTensor<int>({2, 2}, {2});
    auto in3 = test::AsTensor<int>({3, 3}, {2});
    auto add_n_op = ops::AddN(root, {in1, in2, in3});

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({add_n_op}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);

    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({6, 6}, {2}));
}


TEST(TfArthimaticTests, All) {
    // 某一维是否全为 true
    Scope root = Scope::NewRootScope();
    auto in1 = test::AsTensor<int>({1, 1, 1, 1, 1, 1}, {2, 3});
    auto in2 = test::AsTensor<int>({1, 1, 1, 1, 1, 1}, {2, 3});
    auto eq = ops::Equal(root, in1, in2);
    auto attrs = ops::All::KeepDims(true);
    auto all_op = ops::All(root, eq, {0}, attrs);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({all_op.output}, &outputs);

    test::PrintTensorValue<bool>(std::cout, outputs[0]);

    test::ExpectTensorEqual<bool>(outputs[0], test::AsTensor<bool>({true, true, true}, {1, 3}));
}


TEST(TfArthimaticTests, Any) {
    // 某一维任意一个为true
    Scope root = Scope::NewRootScope();
    auto in1 = test::AsTensor<int>({1, 1, 1, 1, 1, 1}, {2, 3});
    auto in2 = test::AsTensor<int>({1, 0, 0, 0, 0, 0}, {2, 3});
    auto eq = ops::Equal(root, in1, in2);
    auto attrs = ops::Any::KeepDims(true);
    auto any_op = ops::Any(root, eq, {0}, attrs);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({any_op.output}, &outputs);

    test::PrintTensorValue<bool>(std::cout, outputs[0]);

    test::ExpectTensorEqual<bool>(outputs[0], test::AsTensor<bool>({true, false, false}, {1, 3}));
}

TEST(TfArthimaticTests, ApproximateEqual) {
    // 近似相等
    Scope root = Scope::NewRootScope();
    auto in1 = test::AsTensor<float>({1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f}, {2, 3});
    auto in2 = test::AsTensor<float>({1.1f, 1.2f, 1.01f, 1.1f, 1.2f, 1.3f}, {2, 3});

    auto attrs = ops::ApproximateEqual::Tolerance(0.2f);
    auto appr_equal_op = ops::ApproximateEqual(root, in1, in2, attrs);
    
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({appr_equal_op.z}, &outputs);

    test::PrintTensorValue<bool>(std::cout, outputs[0]);

    test::ExpectTensorEqual<bool>(outputs[0], test::AsTensor<bool>({true, false, true, true, false, false}, {2, 3}));
}


TEST(TfArthimaticTests, ArgMax) {
    // 取Tensor中响应维度的最大值的索引
    Scope root = Scope::NewRootScope();
    auto in1 = test::AsTensor<int>({0, 1, 1, 1, 1, 1, 2}, {7});
    auto dim = ops::Const(root, 0);
    auto arg_max_op = ops::ArgMax(root, in1, dim);

    ClientSession session(root);
    std::vector<Tensor> outputs;

    session.Run({arg_max_op.output}, &outputs);

    test::PrintTensorValue<int64_t>(std::cout, outputs[0]);

    test::ExpectTensorEqual<int64_t>(outputs[0], test::AsTensor<int64_t>({6}, {}));
}

TEST(TfArthimaticTests, ArgMin) {
    // 取Tensor中响应维度的最小值的索引
    Scope root = Scope::NewRootScope();
    auto in1 = test::AsTensor<int>({0, 1, 1, 1, 1, 1, 2}, {7});
    auto dim = ops::Const(root, 0);
    auto arg_max_op = ops::ArgMin(root, in1, dim);

    ClientSession session(root);
    std::vector<Tensor> outputs;

    session.Run({arg_max_op.output}, &outputs);

    test::PrintTensorValue<int64_t>(std::cout, outputs[0]);

    test::ExpectTensorEqual<int64_t>(outputs[0], test::AsTensor<int64_t>({0}, {}));
}


TEST(TfArthimaticTests, ASin) {
    // 取Tensor 中每个元素的反正弦函数
    Scope root = Scope::NewRootScope();
    auto in1 = test::AsTensor<float>({0.8659266f, 0.7068252f}, {2});

    auto asin_op = ops::Asin(root, in1);

    ClientSession session(root);
    std::vector<Tensor> outputs;

    session.Run({asin_op.y}, &outputs);

    test::PrintTensorValue<float>(std::cout, outputs[0]);

    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({1.047f, 0.785f}, {2}));
}


TEST(TfArthimaticTests, ATan) {
    // 取Tensor 中每个元素的反正切函数
    Scope root = Scope::NewRootScope();
    auto in1 = test::AsTensor<float>({1.731261f, 0.99920404f}, {2});

    auto atan_op = ops::Atan(root, in1);

    ClientSession session(root);
    std::vector<Tensor> outputs;

    session.Run({atan_op.y}, &outputs);

    test::PrintTensorValue<float>(std::cout, outputs[0]);

    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({1.047f, 0.785f}, {2}));
}
