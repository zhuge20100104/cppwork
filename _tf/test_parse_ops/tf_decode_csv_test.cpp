#include <string>
#include <vector>
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


using namespace tensorflow;
using BatchDef = std::initializer_list<tensorflow::int64>;

char const* csv_filepath = "../data/iris.csv";

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

TEST(TfArrayOpsTests, DecodeCSV) {
    // 读取CSV文件
    // https://www.tensorflow.org/versions/r2.6/api_docs/cc/class/tensorflow/ops/decode-c-s-v
    Scope root = Scope::NewRootScope();
    std::fstream ifs {csv_filepath};
    std::string line;
    std::vector<tstring> lines;
    while(std::getline(ifs, line)) {
        lines.emplace_back(tstring(line));
    }

    auto input = test::AsTensor<tensorflow::tstring>(lines, {(long)lines.size()});
    // DecodeCSV函数使用Default Value来推算 输出张量的列数 和类型，不能随便填
    auto decode_csv_op = ops::DecodeCSV(root, input, {Input(1), Input(1.0f), Input(1.0f), Input(1.0f), Input(1.0f), Input(1)});

    ClientSession session(root);
    std::vector<Tensor> outputs;

    session.Run(decode_csv_op.output, &outputs);
    std::cout << outputs[0].DebugString()<< "\n";
    std::cout << outputs[1].DebugString()<< "\n";
    std::cout << outputs[2].DebugString()<< "\n";
    std::cout << outputs[3].DebugString()<< "\n";
    std::cout << outputs[4].DebugString()<< "\n";
    std::cout << outputs[5].DebugString()<< "\n";

    auto index_vals = test::GetTensorValue<int32>(outputs[0]);
    auto huae_length_vals = test::GetTensorValue<float>(outputs[1]);
    test::PrintTensorValue<float>(std::cout, outputs[1]);
    ASSERT_EQ(0, index_vals[0]);
    ASSERT_EQ(5.099999904632568359, huae_length_vals[0]);
    ASSERT_EQ(150, index_vals.size());
    ASSERT_EQ(150, huae_length_vals.size());
}


TEST(TfArrayOpsTests, GenerateIrisDataset) {
    // 生成iris数据集
    // https://www.tensorflow.org/versions/r2.6/api_docs/cc/class/tensorflow/ops/decode-c-s-v
    Scope root = Scope::NewRootScope();

    std::fstream ifs {csv_filepath};
    std::string line;
    std::vector<tstring> lines;
    while(std::getline(ifs, line)) {
        lines.emplace_back(tstring(line));
    }

    auto input = test::AsTensor<tensorflow::tstring>(lines, {(long)lines.size()});
    // DecodeCSV函数使用Default Value来推算 输出张量的列数 和类型，不能随便填
    auto decode_csv_op = ops::DecodeCSV(root, input, {Input(1), Input(1.0f), Input(1.0f), Input(1.0f), Input(1.0f), Input(1)});

    ClientSession session(root);
    std::vector<Tensor> outputs;

    session.Run(decode_csv_op.output, &outputs);
    std::cout << outputs[0].DebugString()<< "\n";
    std::cout << outputs[1].DebugString()<< "\n";
    std::cout << outputs[2].DebugString()<< "\n";
    std::cout << outputs[3].DebugString()<< "\n";
    std::cout << outputs[4].DebugString()<< "\n";
    std::cout << outputs[5].DebugString()<< "\n";
    std::cout << outputs[0].NumElements() << "\n";

    auto input_1 = ops::Reshape(root, outputs[1], {150, 1});
    auto input_2 = ops::Reshape(root, outputs[2], {150, 1});
    auto input_3 = ops::Reshape(root, outputs[3], {150, 1});
    auto input_4 = ops::Reshape(root, outputs[4], {150, 1});

    std::vector<Tensor> outputs_reshape{};
    session.Run({input_1, input_2, input_3, input_4}, &outputs_reshape);

    auto concat_op = ops::Concat(root, {outputs_reshape[0], outputs_reshape[1], outputs_reshape[2], outputs_reshape[3]}, {1});

    std::vector<Tensor> outputs_concat {};
    session.Run({concat_op}, &outputs_concat);
    std::cout << outputs_concat[0].DebugString() << "\n";
}


TEST(TfArrayOpsTests, GenerateIrisDatasetEnhanced) {
    // 生成iris数据集
    // https://www.tensorflow.org/versions/r2.6/api_docs/cc/class/tensorflow/ops/decode-c-s-v
    Scope root = Scope::NewRootScope();

    std::fstream ifs {csv_filepath};
    std::string line;
    std::vector<tstring> lines;
    while(std::getline(ifs, line)) {
        lines.emplace_back(tstring(line));
    }

    ClientSession session(root);

    auto input = test::AsTensor<tensorflow::tstring>(lines, {(long)lines.size()});
    // DecodeCSV函数使用Default Value来推算 输出张量的列数 和类型，不能随便填
    // 1. Decode CSV成列张量
    auto decode_csv_op = ops::DecodeCSV(root, input, {Input(1), Input(1.0f), Input(1.0f), Input(1.0f), Input(1.0f), Input(1)});

    // 2. Reshape 成 (150, 1)， 便于按行concat
    std::vector<Tensor> outputs;
    auto input_1 = ops::Reshape(root, decode_csv_op.output[1], {150, 1});
    auto input_2 = ops::Reshape(root, decode_csv_op.output[2], {150, 1});
    auto input_3 = ops::Reshape(root, decode_csv_op.output[3], {150, 1});
    auto input_4 = ops::Reshape(root, decode_csv_op.output[4], {150, 1});

    // 3. 按行 concat成 (150, 4)，用于iris数据集
    auto concat_op = ops::Concat(root, {Input(input_1), Input(input_2), Input(input_3), Input(input_4)}, {1});

    // 4. Client Session Run，出结果
    std::vector<Tensor> outputs_concat {};
    session.Run({concat_op}, &outputs_concat);
    std::cout << outputs_concat[0].DebugString() << "\n";
    auto shape_src = outputs_concat[0].shape();
    auto shape_expected = TensorShape {150, 4};
    
    std::cout << outputs_concat[0].DebugString() << "\n";

    auto tensor_vals = test::GetTensorValue<float>(outputs_concat[0]);
    ASSERT_EQ(5.099999904632568359, tensor_vals[0]);
    ASSERT_EQ(3.5, tensor_vals[1]);
    ASSERT_EQ(shape_expected, shape_src);
}