
#include "death_handler/death_handler.h"
#include "json/json.hpp"
#include <glog/logging.h>

#include <gtest/gtest.h>
#include "df/df.h"

#include "utils/d_op.h"


using json = nlohmann::json;

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

GTEST_TEST(BDPDbrTests, GetDbrMissingBulkets) {
    auto bdp_bucket_ls = d_op::get_bdp_bucket_list();
    auto db_bucket_ls = d_op::get_databricks_bucket_list();
    auto missing_bucket_ls = d_op::get_missing_bucket_list(bdp_bucket_ls, db_bucket_ls);
    
    auto missing_final = d_op::fx_missing_results(missing_bucket_ls);
    
    auto write_res = d_op::write_to_csv(missing_final);
    ASSERT_TRUE(write_res);
}
