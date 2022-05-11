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


TEST(TfArthimaticTests, BatchMatMul) {
    // BatchMatMul  测试
    // Refers to: https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/batch-mat-mul
    
    // 2 * 1 * 2
    // 2 * 2 * 3
    // = 
    // 2 * 1 * 3
    Scope root = Scope::NewRootScope();
    auto left_ = test::AsTensor<int>({1, 2, 3, 4}, {2, 1, 2});
    /**
     * @brief Left param
     * {{1, 2},
     *  {3, 4}}
     */
    auto right_ = test::AsTensor<int>({1, 2, 3, 4, 1, 2, 3, 4, 5, 6, 7, 8}, {2, 2, 3});
    /**
     * @brief Right param
     *  {{{1, 2, 3}, {4, 1, 2}},
     *   {{3, 4, 5}, {6, 7, 8}}}
     */

    /**
     * @brief Result
     * {{9, 4, 7},
     *  {33, 40, 47}}
     */
    auto batch_op = ops::BatchMatMul(root, left_, right_);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({batch_op.output}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({9, 4, 7, 33, 40, 47}, {2, 1, 3}));
}

TEST(TfArthimaticTests, BatchMatMulAdjXY) {
    // BatchMatMul  测试
    // Refers to: https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/batch-mat-mul
    
    // 2 * 1 * 2
    // 2 * 2 * 3
    // = 
    // 2 * 1 * 3
    Scope root = Scope::NewRootScope();
    auto left_ = test::AsTensor<int>({1, 2, 3, 4}, {2, 2, 1});
    /**
     * @brief Left param
     * {{{1}, 
     *   {2}},
     *  {{3},
     *   {4}}}
     */
    auto right_ = test::AsTensor<int>({1, 2, 3, 4, 1, 2, 3, 4, 5, 6, 7, 8}, {2, 3, 2});
    /**
     * @brief Right param
     *  {{{1, 2}, 
     *   {3, 4}, 
     *   {1, 2}}, 
     *
     *   {{3, 4}, 
     *   {5, 6}, 
     *   {7, 8}}  
     * }
     */
    
   
    /**
     * @brief Result
     * {{5, 11, 5},
     *  {25, 39, 53}}
     */

    auto attrs = ops::BatchMatMul::AdjX(true).AdjY(true);
    auto batch_op = ops::BatchMatMul(root, left_, right_, attrs);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({batch_op.output}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({5, 11, 5, 25, 39, 53}, {2, 1, 3}));
}


TEST(TfArthimaticTests, BatchMatMulV2) {
    // BatchMatMulV2  测试,该操作支持广播
    // Refers to: https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/batch-mat-mul-v2
    
    // 2 * 1 * 2
    // 2 * 1
    // = 
    // 2 * 1 * 1
    Scope root = Scope::NewRootScope();
    auto left_ = test::AsTensor<int>({1, 2, 3, 4}, {2, 1, 2});
    /**
     * @brief Left param
     * {{1, 2},
     *  {3, 4}}
     */
    auto right_ = test::AsTensor<int>({3, 2}, {2, 1});
    /**
     * @brief Right param
     *  {{3}, {2}}
     */

    /**
     * @brief Result
     * {{7}, {17}}
     * */
    auto batch_op = ops::BatchMatMulV2(root, left_, right_);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({batch_op.output}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({7, 17}, {2, 1, 1}));
}


TEST(TfArthimaticTests, BinCount) {
    // BinCount  测试,统计元素中某个索引出现的次数。一般用来对label做统计
    // Refers to: https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/bincount
    // Refers to https://vimsky.com/examples/usage/tensorflow-js-tf-bincount-function.html
    
    Scope root = Scope::NewRootScope();
    auto input_ = test::AsTensor<int>({1, 2, 9, 6, 5, 4, 7,
    4, 7, 4, 3, 2, 4, 2, 5, 1}, {1, 16});
    
    // 0 出现 0次
    // 1 出现 2次
    // 2 出现 3次
    // ...
    auto weights_ = Tensor(DT_INT32, {1, 16});
    test::FillFn<int>(&weights_, [](int i) -> int {
        return 1;
    });
    
    // 空weight表示全1权重，求索引出现的次数
    auto bin_count_op = ops::Bincount(root, input_, 5, weights_);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({bin_count_op.bins}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({0, 2, 3, 1, 4}, {5}));
}

TEST(TfArthimaticTests, BinCountWeights) {
    // BinCount  测试,统计元素中某个索引出现的次数。一般用来对label做统计
    // Refers to: https://www.tensorflow.org/api_docs/cc/class/tensorflow/ops/bincount
    // Refers to https://vimsky.com/examples/usage/tensorflow-js-tf-bincount-function.html
    
    Scope root = Scope::NewRootScope();
    auto input_ = test::AsTensor<int>({1, 2, 9, 6, 5,
    4, 7, 4, 7, 4, 3}, {1, 11});
    // 索引 0对应的weight相加  0
    // 索引 1对应的weight相加  0
    // 索引 2对应的weight相加  2
    // 索引 3对应的weight相加  2
    // 索引 4对应的weight相加  3 + 5 + 8 = 16
    // ...
    auto weights_ = test::AsTensor<int>({0, 2, 5, 8, 9, 3, 5, 5, 3, 8, 2}, {1, 11});
  
    
    // 空weight表示全1权重，求索引出现的次数
    auto bin_count_op = ops::Bincount(root, input_, 8, weights_);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({bin_count_op.bins}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({0, 0, 2, 2, 16, 9, 8, 8}, {8}));
}

