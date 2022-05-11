#include "arr_/arr_.h"
#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include <gtest/gtest.h>


#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;

    Debug::DeathHandler dh;

    google::InitGoogleLogging("./logs.log");
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}


GTEST_TEST(RWTests, ReadCsv) { 
    // 读取CSV文件
    char const* csv_path = "../data/test.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(csv_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);
    ASSERT_EQ(tb_.num_rows(), 2); 
}

GTEST_TEST(RWTests, ReadIpc) { 
    // 读取Arrow IPC 文件
    char const* ipc_path = "../data/test_dst.arrow";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_ipc(ipc_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);
    ASSERT_EQ(tb_.num_rows(), 2); 
}

GTEST_TEST(RWTests, WriteIpc) { 
    // 读取CSV文件并写入IPC文件
    char const* csv_path = "../data/test.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(csv_path, tb);
    auto const& tb_ = *tb;

    char const* write_csv_path = "../data/test_dst.arrow";
    arrow::PrettyPrint(tb_, {}, &std::cerr);
    auto write_res = ArrowUtil::write_ipc(tb_, write_csv_path);
    ASSERT_TRUE(write_res == arrow::Status::OK());
}

GTEST_TEST(RWTests, WriteParquet) { 
    // 写入Parquet文件
    char const* csv_path = "../data/test.csv";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_csv(csv_path, tb);
    auto const& tb_ = *tb;

    char const* write_parquet_path = "../data/test_dst.parquet";
    arrow::PrettyPrint(tb_, {}, &std::cerr);
    auto write_res = ArrowUtil::write_parquet(tb_, write_parquet_path);
    ASSERT_TRUE(write_res == arrow::Status::OK());
}


GTEST_TEST(RWTests, ReadParquet) { 
    // 读取 Parquet
    char const* parquet_path = "../data/test_dst.parquet";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_parquet(parquet_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);
    ASSERT_EQ(tb_.num_rows(), 2); 
}

GTEST_TEST(RWTests, ReadJson) { 
    // 读取Json文件
    char const* json_path = "../data/test.json";
    std::shared_ptr<arrow::Table> tb;
    ArrowUtil::read_json(json_path, tb);
    auto const& tb_ = *tb;
    arrow::PrettyPrint(tb_, {}, &std::cerr);
    ASSERT_EQ(tb_.num_rows(), 2); 
}