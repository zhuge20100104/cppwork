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

int main(int argc, char** argv) {
    Debug::DeathHandler dh;
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

Tensor GetInputTensor() {
    // 从numpy 文件读取 fashion测试集
    auto input_tensor = test::LoadNumPy<float>("../data/x_batch.npy", {10000, 28, 28, 1});
    return input_tensor;
}

Tensor GetGroundtruthTensor() {
    // 从numpy 文件读取 fashion 预测结果
    auto pred_tensor = test::LoadNumPy<int>("../data/y_p.npy", {10000});
    return pred_tensor;
}


Tensor ConvertTensorToInt32Tensor(Tensor const& tensor_) {
    Scope root = Scope::NewRootScope();
    ClientSession session(root);
    std::vector<Tensor> outputs;
    auto dim_ = ops::Const(root, 1);
    auto attrs = ops::ArgMax::OutputType(DT_INT32);
    auto arg_max_op = ops::ArgMax(root, tensor_, dim_, attrs);
    session.Run({arg_max_op.output}, &outputs);
    return outputs[0];
}

int GetMatchNum(Tensor const& pred, Tensor const& actual) {
    Scope root = Scope::NewRootScope();
    ClientSession session(root);
    std::vector<Tensor> outputs;
    auto eq_op = ops::Equal(root, pred, actual);
    auto cast_op = ops::Cast(root, eq_op.z, DT_INT32);
    auto reduce_op = ops::ReduceSum(root, cast_op, 0);
    session.Run({reduce_op.output}, &outputs);
    auto results = test::GetTensorValue<int>(outputs[0]);
    return results[0];
}

TEST(TfFashionModelTest, LoadAndPredict) {
    SavedModelBundleLite bundle;
    SessionOptions session_options;
    RunOptions run_options;

    const string export_dir = "../mnist_model";
    TF_CHECK_OK(LoadSavedModel(session_options, run_options, export_dir,
                              {kSavedModelTagServe}, &bundle));
    
    auto input_tensor = GetInputTensor();

    std::vector<tensorflow::Tensor> out_tensors;
    TF_CHECK_OK(bundle.GetSession()->Run({{"serving_default_flatten_input:0", input_tensor}},
    {"StatefulPartitionedCall:0"}, {}, &out_tensors)); 
    
    auto predict_res = ConvertTensorToInt32Tensor(out_tensors[0]);
    auto labels = GetGroundtruthTensor();
    auto correct = GetMatchNum(predict_res, labels);
    
    std::cout << "Total correct: " << correct << "\n";
    std::cout << "Total datasets: " << labels.NumElements() << "\n"; 
    std::cout << "Accuracy is: " << (float)(correct)/labels.NumElements() << "\n";
}
