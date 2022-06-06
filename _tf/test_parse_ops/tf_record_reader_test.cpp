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

TEST(TfArrayOpsTests, TFRecordReader) {
    // 定长读取文本文件
    // https://www.tensorflow.org/versions/r2.6/api_docs/cc/class/tensorflow/ops/fixed-length-record-reader#classtensorflow_1_1ops_1_1_fixed_length_record_reader_1aa6ad72f08d89016af3043f72912d11eb
    Scope root = Scope::NewRootScope();
    
    auto attrs = ops::FIFOQueue::Capacity(200);
    auto queue_ = ops::FIFOQueue(root.WithOpName("queue"), {DT_STRING}, attrs);

    auto tensor_ = ops::Const(root, {"/cppwork/_tf/test_parse_ops/data/train.tfrecord"});
    auto enque_ = ops::QueueEnqueueMany(root.WithOpName("enque"), queue_, {tensor_});
    auto close_ = ops::QueueClose(root.WithOpName("close"), queue_);

    auto reader = ops::TFRecordReader(root);
    auto read_res = ops::ReaderRead(root.WithOpName("rec_read"), reader, queue_);

    Tensor dense_def0(DT_STRING, {1});
    Tensor dense_def1(DT_INT64, {1});
    // 1. 这个函数很坑，它读取TFRecordReader对象的输出值，read_res.value, 接收两个和输出值类型相同的默认输出值
    // dense_def0 , dense_def1，当然你的数据如果有三个Feature,这里就三个默认值，注意默认值需要与输出值类型相同
    // 2. "img_raw", "label" 是Python侧命名的标签
    // 3. {1}, {1} 是代表单个特征的大小
    // 4. 注意这里支持的类型只有 DT_INT64, DT_STRING和 DT_FLOAT64，其中DT_STRING在Python侧表现为bytearray
    auto parse_op = ops::ParseSingleExample(root.WithOpName("parse_op"), {read_res.value}, {dense_def0, dense_def1}, 0, {}, {"img_raw", "label"}, {}, {{1}, {1}});
    
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
    TF_EXPECT_OK(session->Run({}, {}, {"close"}, nullptr));

    std::vector<Tensor> outputs;
    // 这里 Run 一次会获取一个特征
    for(int i=0; i< 100; ++i) {
        std::vector<Tensor> outputs_res;
        session->Run({}, {parse_op.dense_values[0].name(), parse_op.dense_values[1].name()}, {}, &outputs_res);
        std::cout << outputs_res[0].DebugString() << "\n";
        std::cout << outputs_res[1].DebugString() << "\n";
        auto res = test::GetTensorValue<int64>(outputs_res[1]);
        ASSERT_EQ(i, res[0]);
    }

    TF_EXPECT_OK(qr->Join());
}
