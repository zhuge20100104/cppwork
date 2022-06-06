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

/*
    共轭变换不同于Reshape，会改变张量的顺序
    变换前
    {
        {{1, 2,  3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
        }, 
        {
        {13, 14, 15, 16},
        {17, 18, 19, 20},
        {21, 22, 23, 24}
        }
    }

    变换后
    {
        {
            {1, 2, 3, 4},
            {13,14, 15, 16}
        },

        {
            { 5, 6, 7, 8},
            {17, 18, 19, 20}
        },

        {
            {9, 10, 11, 12},
            {21, 22, 23, 24}
        }
    }

    从上下各拿一行，生成3*2*4
*/

TEST(TfArrayOpsTests, ConjugateTranspose) {
    // 维度转换API
    // Refers to https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/conjugate-transpose
    Scope root = Scope::NewRootScope();
    auto input_tensor = test::AsTensor<int>({1, 2,  3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24}, {2, 3, 4});
    auto perm = test::AsTensor<int>({1, 0, 2}, {3});
    auto conjugate_op = ops::ConjugateTranspose(root, input_tensor, perm);
   
    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({conjugate_op}, &outputs);
    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({1, 2, 3, 4, 13,14, 15, 16, 5, 6, 7, 8, 17, 18, 19, 20, 9, 10, 11, 12, 21, 22, 23, 24}, {3, 2, 4}));
}