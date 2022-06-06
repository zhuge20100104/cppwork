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

TEST(TfArrayOpsTests, IdentityRecordReader) {
    // 定长读取文本文件
    // https://www.tensorflow.org/versions/r2.6/api_docs/cc/class/tensorflow/ops/fixed-length-record-reader#classtensorflow_1_1ops_1_1_fixed_length_record_reader_1aa6ad72f08d89016af3043f72912d11eb
    Scope root = Scope::NewRootScope();
    
    auto attrs = ops::FIFOQueue::Capacity(100);
    auto queue_ = ops::FIFOQueue(root.WithOpName("queue"), {DT_STRING}, attrs);

    auto tensor_ = ops::Const(root, {"abcd", "efgh", "ijkl"});
    auto enque_ = ops::QueueEnqueueMany(root.WithOpName("enque"), queue_, {tensor_});
    auto close_ = ops::QueueClose(root.WithOpName("close"), queue_);

    auto reader = ops::IdentityReader(root);
    auto read_res = ops::ReaderRead(root.WithOpName("identity_read"), reader, queue_);
    
    SessionOptions options;
    std::unique_ptr<Session> session(NewSession(options));
    GraphDef graph_def;
    TF_EXPECT_OK(root.ToGraphDef(&graph_def));
    session->Create(graph_def);

    QueueRunnerDef queue_runner_def =
      test::BuildQueueRunnerDef("queue", {"enque"}, "close", "", {tensorflow::error::CANCELLED});
    std::unique_ptr<QueueRunner> qr;
    TF_EXPECT_OK(QueueRunner::New(queue_runner_def, &qr));
    TF_CHECK_OK(qr->Start(session.get()));

    TF_EXPECT_OK(session->Run({}, {}, {"enque"}, nullptr));

    std::vector<Tensor> outputs;
    
    std::array<std::string, 3> arr {"abcd", "efgh", "ijkl"};
    
    for(int i=0; i< 3; ++i) {
        session->Run({}, {read_res.value.name()}, {}, &outputs);
        if(outputs.size() > 0) {
            for(auto const& output: outputs) {
                std::cout << output.DebugString() << "\n";
            }
            test::ExpectTensorEqual<tstring>(outputs[0], test::AsTensor<tstring>({arr[i]}, {}));
        }
    }

    TF_EXPECT_OK(session->Run({}, {}, {"close"}, nullptr));
    TF_EXPECT_OK(qr->Join());
}
