#include <tensorflow/c/c_api.h>

#include <vector>

#include "absl/synchronization/barrier.h"
#include "tf_/tensor_testutil.h"
#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/lib/core/status_test_util.h"
#include "tensorflow/core/lib/core/threadpool.h"
#include "tensorflow/core/lib/core/threadpool_options.h"
#include "tensorflow/core/platform/test.h"
#include "tensorflow/core/util/work_sharder.h"
#include "third_party/eigen3/unsupported/Eigen/CXX11/Tensor"

using namespace tensorflow;

TEST(ClientSessionTests, Feed) {

    Scope root = Scope::NewRootScope();
    auto a = ops::Placeholder(root, DT_INT32);
    auto b = ops::Placeholder(root, DT_INT32);
    auto c = ops::Add(root, a, b);
    
    
    ClientSession session(root);
    std::vector<Tensor> outputs;
    TF_EXPECT_OK(session.Run({{a, 1}, {b, 41}}, {c}, &outputs));
    std::cout << TF_Version() << "\n";
    test::ExpectTensorEqual<int>(outputs[0], test::AsTensor<int>({42}, {}));
}
