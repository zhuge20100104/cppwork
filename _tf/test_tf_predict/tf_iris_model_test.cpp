#include <tensorflow/c/c_api.h>

#include "death_handler/death_handler.h"

#include "tensorflow/cc/saved_model/constants.h"
#include "tensorflow/cc/saved_model/loader.h"
#include "tensorflow/cc/saved_model/signature_constants.h"
#include "tensorflow/cc/saved_model/tag_constants.h"
#include "tensorflow/cc/client/client_session.h"

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
#include "df/df.h"

using namespace tensorflow;

using BatchDef = std::initializer_list<tensorflow::int64>;
char const* data_csv = "../data/iris.csv";

int main(int argc, char** argv) {
    Debug::DeathHandler dh;
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

std::vector<float> GetInputBatches() {
    CLDataFrame df;
    df.read(data_csv, hmdf::io_format::csv2, false);
    auto huae_length_vec = df.get_column<float>("花萼长度");
    auto huae_width_vec = df.get_column<float>("花萼宽度");
    auto huab_length_vec = df.get_column<float>("花瓣长度");
    auto huab_width_vec = df.get_column<float>("花瓣宽度");

    std::vector<float> res{};
    res.reserve(4 * huae_length_vec.size());
    for(std::size_t i=0; i<huae_length_vec.size(); ++i) {
        res.emplace_back(huae_length_vec[i]);
        res.emplace_back(huae_width_vec[i]);
        res.emplace_back(huab_length_vec[i]);
        res.emplace_back(huab_width_vec[i]);
    }
    return res;
}

std::vector<int> GetOutputBatches() {
    CLDataFrame df;
    df.read(data_csv, hmdf::io_format::csv2, false);
    auto labels = df.get_column<int>("类别");
    return labels;
}

std::vector<int> ConvertTensorToIndexValue(Tensor const& tensor_) {
    auto tensor_res = test::GetTensorValue<float>(tensor_);
    std::vector<int> predict_res{};
    for(int i=0; i<tensor_res.size(); ++i) {
        if(i!=0 && (i+1)%3==0) {
            auto max_idx = std::max_element(tensor_res.begin() + (i-2), tensor_res.begin() + (i+1)) -(tensor_res.begin() + (i-2));
            predict_res.emplace_back((int)max_idx);
        }    
    }
    return predict_res;
}

Tensor MakeTensor(std::vector<float> const& batch, BatchDef const& batch_def) {
    Tensor t(DT_FLOAT,
        TensorShape(batch_def));
    for (int i = 0; i < batch.size(); ++i) {
      t.flat<float>()(i) = batch[i];
    }
    return t;
}

TEST(TfIrisModelTest, LoadAndPredict) {
    SavedModelBundleLite bundle;
    SessionOptions session_options;
    RunOptions run_options;

    const string export_dir = "../iris_model";
    TF_CHECK_OK(LoadSavedModel(session_options, run_options, export_dir,
                              {kSavedModelTagServe}, &bundle));
    
    auto input_batches = GetInputBatches();
    auto input_tensor = MakeTensor(input_batches, {150, 4});

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
