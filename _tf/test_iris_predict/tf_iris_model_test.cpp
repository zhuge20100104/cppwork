#include <fstream>

#include <tensorflow/c/c_api.h>

#include "death_handler/death_handler.h"

#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/saved_model/constants.h"
#include "tensorflow/cc/saved_model/loader.h"
#include "tensorflow/cc/saved_model/signature_constants.h"
#include "tensorflow/cc/saved_model/tag_constants.h"

#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/lib/io/path.h"
#include "tensorflow/core/platform/env.h"
#include "tensorflow/core/platform/init_main.h"
#include "tensorflow/core/platform/logging.h"
#include "tensorflow/core/platform/types.h"

#include <vector>
#include "tensorflow/core/public/session.h"
#include "tensorflow/cc/ops/const_op.h"
#include "tf_/tensor_testutil.h"
#include "tensorflow/core/framework/node_def_util.h"
#include "tensorflow/core/lib/core/status_test_util.h"
#include "tensorflow/core/platform/test.h"


using namespace tensorflow;

using BatchDef = std::initializer_list<tensorflow::int64>;
char const* data_csv = "../data/iris.csv";

int main(int argc, char** argv) {
    Debug::DeathHandler dh;
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

// 获取CSV文件行
std::vector<tstring> GetCSVLines() {
    std::fstream ifs {data_csv};
    std::string line;
    std::vector<tstring> lines;
    while(std::getline(ifs, line)) {
        lines.emplace_back(tstring(line));
    }
    return lines;
}

Tensor GetInputTensor() {
    // 生成iris数据集
    // https://www.tensorflow.org/versions/r2.6/api_docs/cc/class/tensorflow/ops/decode-c-s-v
    Scope root = Scope::NewRootScope();
    ClientSession session(root);
    
    auto lines = GetCSVLines();
    auto input = test::AsTensor<tensorflow::tstring>(lines, {(long)lines.size()});
    // DecodeCSV函数使用Default Value来推算 输出张量的列数 和类型，不能随便填
    // 1. Decode CSV成列张量
    auto decode_csv_op = ops::DecodeCSV(root, input, {Input(1), Input(1.0f), Input(1.0f), Input(1.0f), Input(1.0f), Input(1)});

    // 2. Reshape 成 (150, 1)， 便于按行concat
    auto input_1 = ops::Reshape(root, decode_csv_op.output[1], {150, 1});
    auto input_2 = ops::Reshape(root, decode_csv_op.output[2], {150, 1});
    auto input_3 = ops::Reshape(root, decode_csv_op.output[3], {150, 1});
    auto input_4 = ops::Reshape(root, decode_csv_op.output[4], {150, 1});

    // 3. 按行 concat成 (150, 4)，用于iris数据集
    auto concat_op = ops::Concat(root, {Input(input_1), Input(input_2), Input(input_3), Input(input_4)}, {1});

    // 4. Client Session Run，出结果
    std::vector<Tensor> outputs_concat {};
    session.Run({concat_op}, &outputs_concat);
    return outputs_concat[0];
}

std::vector<int> GetOutputBatches() {
    Scope root = Scope::NewRootScope();

    auto lines = GetCSVLines();
    auto input = test::AsTensor<tensorflow::tstring>(lines, {(long)lines.size()});
    // DecodeCSV函数使用Default Value来推算 输出张量的列数 和类型，不能随便填
    auto decode_csv_op = ops::DecodeCSV(root, input, {Input(1), Input(1.0f), Input(1.0f), Input(1.0f), Input(1.0f), Input(1)});

    ClientSession session(root);
    std::vector<Tensor> outputs;

    session.Run(decode_csv_op.output, &outputs);
    return test::GetTensorValue<int>(outputs[5]);
}


std::vector<int> ConvertTensorToIndexValue(Tensor const& tensor_) {
    Scope root = Scope::NewRootScope();
    ClientSession session(root);
    std::vector<Tensor> outputs;
    auto dim_ = ops::Const(root, 1);
    auto attrs = ops::ArgMax::OutputType(DT_INT32);
    auto arg_max_op = ops::ArgMax(root, tensor_, dim_, attrs);
    session.Run({arg_max_op.output}, &outputs);
    auto predict_res = test::GetTensorValue<int>(outputs[0]); 
    return predict_res;
}

TEST(TfIrisModelTest, LoadAndPredict) {
    SavedModelBundleLite bundle;
    SessionOptions session_options;
    RunOptions run_options;

    const string export_dir = "../iris_model";
    TF_CHECK_OK(LoadSavedModel(session_options, run_options, export_dir,
                              {kSavedModelTagServe}, &bundle));
    
    auto input_tensor = GetInputTensor();

    std::vector<tensorflow::Tensor> out_tensors;
    TF_CHECK_OK(bundle.GetSession()->Run({{"serving_default_input_1:0", input_tensor}},
    {"StatefulPartitionedCall:0"}, {}, &out_tensors)); 

    std::cout << "Print Tensor Value\n";
    test::PrintTensorValue<float>(std::cout, out_tensors[0], 3);
    std::cout << "\n";

    std::cout << "Print Index Value\n";
    auto predict_res = ConvertTensorToIndexValue(out_tensors[0]);
    for(auto ele: predict_res) {
        std::cout << ele << "\n";
    }

    auto labels = GetOutputBatches();
    int correct {0};
    for(int i=0; i<predict_res.size(); ++i) {
        if(predict_res[i] == labels[i]) {
            ++ correct;
        }
    }
    
    std::cout << "Total correct: " << correct << "\n";
    std::cout << "Total datasets: " << labels.size() << "\n"; 
    std::cout << "Accuracy is: " << (float)(correct)/labels.size() << "\n";
}
