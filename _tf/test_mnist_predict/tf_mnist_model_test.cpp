#include <tensorflow/c/c_api.h>

#include "death_handler/death_handler.h"

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
#include <opencv2/imgproc.hpp>
#include "img_util/img_util.h"

using namespace tensorflow;

using BatchDef = std::initializer_list<tensorflow::int64>;
int const img_width = 28;
int const img_height = 28;

int main(int argc, char** argv) {
    Debug::DeathHandler dh;
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

std::vector<float> GetInputData(std::string const& file_name) {
    auto raw_data = cv::imread(file_name);
    cv::Mat scaled_data {};

    // 1. C++ 先resize 参考这个 https://learnopencv.com/image-resizing-with-opencv/
    cv::resize(raw_data, scaled_data, cv::Size(img_width, img_height),  cv::INTER_LANCZOS4);

    // 2. 再 BGR 2 GRAY
    cv::Mat gray_data {};
    cv::cvtColor(scaled_data, gray_data, cv::COLOR_BGR2GRAY);

    // 3. 再转换成 std::vector 参考 Mat to vector https://stackoverflow.com/questions/26681713/convert-mat-to-array-vector-in-opencv
    auto gray_conti = gray_data.isContinuous()? gray_data: gray_data.clone();
    cv::Mat flat = gray_data.reshape(1, gray_data.total()*gray_data.channels());
    std::vector<uint8_t> vec = flat;

    // 4. 图像反色 255 - src Array的颜色, 这个就用std::transform算子 https://blog.csdn.net/weixin_42100963/article/details/106446563
    // 5.  再除以255.0f
    std::vector<float> res_tensor_data {};
    res_tensor_data.resize(vec.size());

    std::transform(vec.begin(), vec.end(), res_tensor_data.begin(), [](auto ele) {
        return ((float)(255 - ele))/ 255.0f;
    });

    return res_tensor_data;
}


std::vector<int> ConvertTensorToIndexValue(Tensor const& tensor_) {
    auto tensor_res = test::GetTensorValue<float>(tensor_);
    std::vector<int> predict_res{};

    for(int i=0; i<tensor_res.size(); ++i) {
        if(i!=0 && (i+1)%10==0) {
            auto max_idx = std::max_element(tensor_res.begin() + (i-9), tensor_res.begin() + (i+1)) - (tensor_res.begin() + (i-9));
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

TEST(TfMnistModelTest, LoadAndPredict) {
    SavedModelBundleLite bundle;
    SessionOptions session_options;
    RunOptions run_options;

    const string export_dir = "../mnist_model";
    TF_CHECK_OK(LoadSavedModel(session_options, run_options, export_dir,
                              {kSavedModelTagServe}, &bundle));
    
    std::cout << "input the number of test pictures: \n";
    int pre_num{0};
    std::cin >> pre_num;

    for(int i=0; i<pre_num; ++i) {
        // 1. 获取输入图片路径
        std::cout << "the path of test picture: \n";
        std::string img_path{};
        std::cin >> img_path;

        // 2. 获取输入图片数据
        auto input_batches = GetInputData(img_path);

        // 3. 转换成神经网络需要的tensor 形状
        auto input_tensor = MakeTensor(input_batches, {1, 28, 28, 1});

        // 4. 运行预测过程
        std::vector<tensorflow::Tensor> out_tensors;
        TF_CHECK_OK(bundle.GetSession()->Run({{"serving_default_flatten_input:0", input_tensor}},
        {"StatefulPartitionedCall:0"}, {}, &out_tensors)); 
        
        // 5. 打印tensor 值
        std::cout << "Print Tensor Value\n";
        test::PrintTensorValue<float>(std::cout, out_tensors[0], 10);
        std::cout << "\n";

        // 6. 将tensor值转换成数字值，打印预测结果
        auto predict_res = ConvertTensorToIndexValue(out_tensors[0]);
        std::cout << "Predict result: " << predict_res[0] << "\n";
    }
}
