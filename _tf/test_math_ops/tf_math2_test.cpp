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


TEST(TfArthimaticTests, Bucketize) {
    // Bucketize 将张量元素值按照 边界数组分桶，返回第一个大于当前元素的边界数组元素的位置索引
    // Refers to: https://tensorflow.google.cn/versions/r2.6/api_docs/cc/class/tensorflow/ops/bucketize?hl=zh-cn&authuser=0
    // Refers to https://www.jianshu.com/p/378a7678a533
    
    Scope root = Scope::NewRootScope();
    auto input_ = test::AsTensor<int>({-5, 10000, 150, 10, 5, 100}, {3, 2});
    
    // 分桶操作
    auto bucketize_op = ops::Bucketize(root, input_, {0.0f, 10.0f, 100.0f});

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({bucketize_op.output}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({0, 3, 3, 2, 1, 3}, {3, 2}));
}


TEST(TfArthimaticTests, Cast) {
    // Cast 转换张量元素类型
    // Refers to: https://tensorflow.google.cn/versions/r2.6/api_docs/cc/class/tensorflow/ops/cast?hl=zh-cn&authuser=0#classtensorflow_1_1ops_1_1_cast_1a82145cd417863a5aa1a282e8db95e9cc
    
    Scope root = Scope::NewRootScope();
    auto input_ = test::AsTensor<int>({-5, 10000, 150, 10, 5, 100}, {3, 2});
    
    // 转换操作
    auto cast_op = ops::Cast(root, input_, DT_FLOAT);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({cast_op.y}, &outputs);

    test::PrintTensorValue<float>(std::cout, outputs[0]);
    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({-5, 10000, 150, 10, 5, 100}, {3, 2}));
}


TEST(TfArthimaticTests, Ceil) {
    // Ceil 张量元素向上取整
    // Refers to: https://tensorflow.google.cn/versions/r2.6/api_docs/cc/class/tensorflow/ops/ceil?hl=zh-cn&authuser=0
    
    Scope root = Scope::NewRootScope();
    auto input_ = test::AsTensor<float>({1.1, 2.2, 3.3}, {3});
    
    // 向上取整操作
    auto ceil_op = ops::Ceil(root, input_);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({ceil_op.y}, &outputs);

    test::PrintTensorValue<float>(std::cout, outputs[0]);
    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({2, 3, 4}, {3}));
}


TEST(TfArthimaticTests, ClipByValue) {
    // ClipByValue 用最大边界和最小边界裁切张量
    // Refers to: https://tensorflow.google.cn/versions/r2.6/api_docs/cc/class/tensorflow/ops/clip-by-value?hl=zh-cn&authuser=0
    
    Scope root = Scope::NewRootScope();
    auto input_ = test::AsTensor<int>({-1, 0, 10, 16, 20, 8, 7, 21}, {8});
    
    // 裁切操作
    auto clip_op = ops::ClipByValue(root, input_, 0, 15);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({clip_op.output}, &outputs);

    test::PrintTensorValue<int>(std::cout, outputs[0]);
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({0, 0, 10, 15, 15, 8, 7, 15}, {8}));
}

TEST(TfArthimaticTests, Complex) {
    // Complex转换两个张量为一个复数张量
    // Refers to: https://tensorflow.google.cn/versions/r2.6/api_docs/cc/class/tensorflow/ops/complex?hl=zh-cn&authuser=0
    Scope root = Scope::NewRootScope();
    auto real_ = test::AsTensor<float>({2.25f, 3.25f}, {2});
    auto image_ = test::AsTensor<float>({4.75f, 5.75f}, {2});
    
    // 转换为复数
    auto complex_op = ops::Complex(root, real_, image_);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({complex_op.out}, &outputs);
    test::PrintTensorValue<complex64>(std::cout, outputs[0]);
    test::ExpectTensorEqual<complex64>(outputs[0], test::AsTensor<complex64>({
        {2.25f, 4.75f}, {3.25f, 5.75f}
    }, {2}));
}

TEST(TfArthimaticTests, ComplexAbs) {
    // ComplexAbs求复数的绝对值
    // Refers to: https://tensorflow.google.cn/versions/r2.6/api_docs/cc/class/tensorflow/ops/complex-abs?hl=zh-cn&authuser=0
    Scope root = Scope::NewRootScope();
    auto input_ = test::AsTensor<complex64>({{3.0f, 4.0f}}, {1});
    
    // 求复数的模的绝对值
    auto complex_abs_op = ops::ComplexAbs(root, input_);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({complex_abs_op.y}, &outputs);
    test::PrintTensorValue<float>(std::cout, outputs[0]);
    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({5.0f}, {1}));
}


TEST(TfArthimaticTests, ComplexConj) {
    // ComplexConj求复数的复数共轭 a + bj -> a - bj
    // Refers to: https://tensorflow.google.cn/versions/r2.6/api_docs/cc/class/tensorflow/ops/conj?hl=zh-cn&authuser=0#classtensorflow_1_1ops_1_1_conj_1ac0a0d5db60f5731bf0fd10e22a70590c
    Scope root = Scope::NewRootScope();
    auto input_ = test::AsTensor<complex64>({{-2.25, 4.75}, {3.25, 5.75}}, {2});
    
    // 求复数的共轭
    auto conj_op = ops::Conj(root, input_);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({conj_op.output}, &outputs);
    test::PrintTensorValue<complex64>(std::cout, outputs[0]);
    test::ExpectTensorEqual<complex64>(outputs[0], test::AsTensor<complex64>({{-2.25f, -4.75f}, {3.25f, -5.75f}}, {2}));
}

TEST(TfArthimaticTests, Cos) {
    // Cos 求数据的余弦值
    // Refers to: https://tensorflow.google.cn/versions/r2.6/api_docs/cc/class/tensorflow/ops/cos?hl=zh-cn&authuser=0
    Scope root = Scope::NewRootScope();
    auto input_ = test::AsTensor<float>({-9.0f, -0.5f, 1.0f, 1.2f}, {4});
    
    // 求余弦值
    auto cos_op = ops::Cos(root, input_);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({cos_op.y}, &outputs);
    test::PrintTensorValue<float>(std::cout, outputs[0]);
    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({-0.9111302495002746582, 0.877582550048828125, 0.540302276611328125, 0.36235770583152771}, {4}));
}

TEST(TfArthimaticTests, Cross) {
    // Cross 求向量的叉乘，向量叉乘只适用于3维空间向量
    // 向量叉乘的含义: https://blog.csdn.net/qq_36056219/article/details/109057649
    // Refers to: https://tensorflow.google.cn/versions/r2.6/api_docs/cc/class/tensorflow/ops/cross?hl=zh-cn&authuser=0
    Scope root = Scope::NewRootScope();
    auto a_ = test::AsTensor<float>({1.0f, 2.0f, -3.0f}, {3});
    auto b_ = test::AsTensor<float>({2.0f, 3.0f, 4.0f}, {3});
    // 求向量叉乘
    auto cross_op = ops::Cross(root, a_, b_);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({cross_op.product}, &outputs);
    test::PrintTensorValue<float>(std::cout, outputs[0]);
    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({17.0f, -10.0f, -1.0f}, {3}));
}

TEST(TfArthimaticTests, Cumprod) {
    //  Cumprod 沿轴方向计算张量的累积乘积
    // Refers to: https://tensorflow.google.cn/versions/r2.6/api_docs/cc/class/tensorflow/ops/cumprod?hl=zh-cn&authuser=0
    Scope root = Scope::NewRootScope();
    auto input_ = test::AsTensor<float>({1.0f, 2.0f, -3.0f}, {3});
    // 求张量的累积乘积
    auto cump_prod_op = ops::Cumprod(root, input_, 0);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({cump_prod_op.out}, &outputs);
    test::PrintTensorValue<float>(std::cout, outputs[0]);
    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({1.0f, 2.0f, -6.0f}, {3}));
}

TEST(TfArthimaticTests, CumprodReverse) {
    //  Cumprod 沿轴方向反向计算张量的累积乘积
    // Refers to: https://tensorflow.google.cn/versions/r2.6/api_docs/cc/class/tensorflow/ops/cumprod?hl=zh-cn&authuser=0
    Scope root = Scope::NewRootScope();
    auto input_ = test::AsTensor<float>({1.0f, 2.0f, -3.0f}, {3});
    auto reverse_attr = ops::Cumprod::Reverse(true);
    // 求张量的累积乘积
    auto cump_prod_op = ops::Cumprod(root, input_, 0, reverse_attr);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({cump_prod_op.out}, &outputs);
    test::PrintTensorValue<float>(std::cout, outputs[0]);
    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({-6.0f, -6.0f, -3.0f}, {3}));
}

// TODO: Add cum sum cases
TEST(TfArthimaticTests, CumSum) {
    //  Cumprod 沿轴方向计算张量的累积乘积
    // Refers to: https://tensorflow.google.cn/versions/r2.6/api_docs/cc/class/tensorflow/ops/cumprod?hl=zh-cn&authuser=0
    Scope root = Scope::NewRootScope();
    auto input_ = test::AsTensor<float>({1.0f, 2.0f, -3.0f}, {3});
    // 求张量的累积乘积
    auto cump_prod_op = ops::Cumprod(root, input_, 0);

    ClientSession session(root);
    std::vector<Tensor> outputs;
    session.Run({cump_prod_op.out}, &outputs);
    test::PrintTensorValue<float>(std::cout, outputs[0]);
    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({1.0f, 2.0f, -6.0f}, {3}));
}