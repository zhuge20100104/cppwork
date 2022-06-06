
#include "tensorflow/cc/training/queue_runner.h"

#include <string>
#include <vector>

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

TEST(TfRandomUniformTests, RandomUniform) {
    // 均匀分布测试
    Scope root = Scope::NewRootScope();
    ops::RandomUniform::Attrs attrs {1, 2};
    
    Output uni = ops::RandomUniform(root.WithOpName("uni"), {2, 2}, DataType::DT_FLOAT, attrs);
    ClientSession session(root);

    std::vector<Tensor> outputs;
    session.Run({uni}, &outputs);
    // 打印Tensor值
    test::PrintTensorValue<float>(std::cout, outputs[0]);

    // 打印Tensor信息
    std::cout << outputs[0].DebugString() << "\n";

    test::ExpectTensorEqual<float>(outputs[0], test::AsTensor<float>({0.4063967466354370117, 0.8575996160507202148, 0.05539584159851074219, 0.08587229251861572266}, {2, 2}));
}
