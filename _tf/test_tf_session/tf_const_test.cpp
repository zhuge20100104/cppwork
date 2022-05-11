#include <tensorflow/c/c_api.h>
#include <glog/logging.h>
#include "death_handler/death_handler.h"
#include <vector>
#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/const_op.h"
#include "tf_/tensor_testutil.h"
#include "tensorflow/core/framework/node_def_util.h"
#include "tensorflow/core/lib/core/status_test_util.h"
#include "tensorflow/core/platform/test.h"

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


TEST(TfConstTest, Basic) {
    // 基本常量方法测试
    Scope root = Scope::NewRootScope();
    auto c = ops::Const(root, {1, 5});
    
    TF_EXPECT_OK(root.status());

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({c}, &outputs);

    // 打印Tensor值
    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({1, 5}, {2}));
}
