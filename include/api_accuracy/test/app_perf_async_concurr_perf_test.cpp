#include <glog/logging.h>
#include <gtest/gtest.h>

#include "api_accuracy/cases/app_perf_cases.h"
#include "api_accuracy/test_cfg.h"
#include "api_accuracy/utils/async_concurr_decorator.hpp"
#include "api_accuracy/utils/beans.h"
#include "api_accuracy/utils/compare.h"
#include "api_accuracy/utils/data_op.h"
#include "api_accuracy/utils/funcs.h"
#include "api_accuracy/utils/io_util.h"
#include "api_accuracy/utils/req.h"
#include "death_handler/death_handler.h"
#include "df/df.h"
#include "json/json.hpp"
#include "pystring/pystring.h"

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

class AppPerfAsyncConcurrPerfTests : public testing::Test {
   protected:
    virtual void SetUp() { perf_cases = app_perf_async_concurr_perf_cases; }

    virtual void TearDown() {}

    std::vector<Case> perf_cases;
};

TEST_F(AppPerfAsyncConcurrPerfTests, TestPerfCases) {
    json pt_list;
    auto req_test_func = make_async_concurr_decorator(
        Req::make_a_async_api_query_and_get_report_url);

    for (auto&& perf_case : perf_cases) {
        auto url = perf_case.url;
        auto i = 0;

        LOG(INFO) << url << "\n";
        auto req_result = req_test_func(url);
        
        json pt{
            {"1name", url},
            {"2avg_time", req_result.avg_time},
            {"3min_time", req_result.min_time},
            {"4max_time", req_result.max_time},
            {"5fail_count", req_result.fail_count},
            {"6total_count", req_result.total_count},
        };
        pt_list.emplace_back(pt);
    }

    auto rs_csv_path = "../result/result_async_concurr.csv";
    auto df = df_op::convert_json_to_df(pt_list, {"1name"});
    df_op::write_to_csv(df, rs_csv_path);
}
