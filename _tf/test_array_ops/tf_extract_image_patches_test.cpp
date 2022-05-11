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

TEST(TfArrayOpsTests, ExtractImagePatches1) {
    // Extract patches from images and put them in the "depth" output dimension
    // Refers to https://www.tensorflow.org/versions/r2.6/api_docs/cc/class/tensorflow/ops/extract-image-patches
    // Refers to https://blog.csdn.net/weixin_43935696/article/details/117694657
    Scope root = Scope::NewRootScope();
    Tensor source_t{DT_INT32, {10, 10}}; 
    test::FillIota<int>(&source_t, 1);

    auto reshape_op = ops::Reshape(root, source_t, {1, 10, 10, 1});

    auto extract_img_patch_op = ops::ExtractImagePatches(root, reshape_op.output, {1, 3, 3, 1}, {1, 5, 5, 1}, {1, 1, 1, 1}, "VALID");

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({extract_img_patch_op.patches}, &outputs);

    std::cout << outputs[0].DebugString() << "\n";

    test::PrintTensorValue<int>(std::cout, outputs[0], 9);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({1, 2, 3, 11, 12, 13, 21, 22, 23,
                                                                  6, 7,	8, 16, 17, 18, 26, 27, 28,
                                                                  51, 52, 53, 61, 62, 63, 71, 72, 73,
                                                                  56, 57, 58, 66, 67, 68, 76, 77, 78},
                                                                    {1, 2, 2, 9}));
}


TEST(TfArrayOpsTests, ExtractImagePatches2) {
    // Extract patches from images and put them in the "depth" output dimension
    // Refers to https://www.tensorflow.org/versions/r2.6/api_docs/cc/class/tensorflow/ops/extract-image-patches
    // Refers to https://blog.csdn.net/weixin_43935696/article/details/117694657
    Scope root = Scope::NewRootScope();
    Tensor source_t{DT_INT32, {10, 10}}; 
    test::FillIota<int>(&source_t, 1);

    auto reshape_op = ops::Reshape(root, source_t, {1, 10, 10, 1});

    auto extract_img_patch_op = ops::ExtractImagePatches(root, reshape_op.output, {1, 3, 3, 1}, {1, 5, 5, 1}, {1, 2, 2, 1}, "VALID");

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({extract_img_patch_op.patches}, &outputs);

    std::cout << outputs[0].DebugString() << "\n";

    test::PrintTensorValue<int>(std::cout, outputs[0], 9);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({1, 3, 5, 21, 23, 25, 41, 43, 45,
                                                                  6, 8,	10, 26,	28,	30,	46,	48,	50,
                                                                  51, 53, 55, 71, 73, 75, 91, 93, 95,
                                                                  56, 58, 60, 76, 78, 80, 96, 98, 100},
                                                                   {1, 2, 2, 9}));
}