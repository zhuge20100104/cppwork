#include "api_accuracy/cases/app_perf_cases.h"
#include "api_accuracy/test_cfg.h"
#include "api_accuracy/utils/req.h"
#include "api_accuracy/utils/io_util.h"
#include "api_accuracy/utils/funcs.h"
#include "api_accuracy/utils/beans.h"
#include "api_accuracy/utils/compare.h"
#include "api_accuracy/utils/async_decorator.hpp"
#include "api_accuracy/utils/data_op.h"

#include "df/df.h"

#include "pystring/pystring.h"
#include "json/json.hpp"
#include "death_handler/death_handler.h"

#include <glog/logging.h>

#include <gtest/gtest.h>


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


class AppPerfAsyncPerfTests : public testing::Test {
   protected:
    static void SetUpTestCase() { perf_cases = app_perf_async_perf_cases; }

    static void TearDownTestCase() {}

    static std::vector<Case> perf_cases;
};

std::vector<Case> AppPerfAsyncPerfTests::perf_cases {};



TEST_F(AppPerfAsyncPerfTests, TestPerfCases) {
    json pt_list;
    auto req_test_func = make_async_decorator(Req::make_a_async_api_query_and_get_report_url); 

    for (auto&& perf_case : perf_cases) {
        auto is_running = true;
        auto url = perf_case.url;
        auto i = 0;
        while(is_running) {
            LOG(INFO) << url << "\n";
            auto req_result = req_test_func(url);
            auto is_running = req_result.status;
            if(!is_running) {
                json pt {
                    {"1name", ""},
                    {"2apps_count", ""},
                    {"3data_chunks", ""}, 
                    {"4raw_size", ""}, 
                    {"5decompress_size", ""},
                    {"6response_time", ""},
                };

                pt_list.emplace_back(pt);
                pt_list.emplace_back(pt);
                LOG(INFO) << "Met End data error, break..." << "\n";
                break;
            }
            std::string res_content = (std::string) req_result.res["result"].get<std::string>();
            std::string report_url = (std::string)req_result.res["report_url"].get<std::string>();
            auto response_time = req_result.avg_time;
            auto zipped_content = Req::make_a_async_zipped_query(report_url);

            auto raw_size = (float)(zipped_content.size()) / (float)(1024);
            auto decompress_size = (float)(res_content.size()) / (float)(1024);
        
            LOG(INFO) << "Raw size: " << raw_size << "\n";
            LOG(INFO) << "Decompressed size:" << decompress_size << "\n";
            auto res_js = json::parse(res_content);
            auto d_op = data_op(res_js["data"]);
            auto apps_count = d_op.get_apps_count();
            auto data_chunks = d_op.get_data_chunks();
            json pt_value  {
                {"1name",  url},
                {"2apps_count", apps_count},
                    {"3data_chunks", data_chunks}, 
                    {"4raw_size", raw_size}, 
                    {"5decompress_size", decompress_size},
                    {"6response_time", response_time}
            };
            pt_list.emplace_back(std::move(pt_value));
            ++i;
            auto ret_val = adjust_req_url_date(url, i);
            auto end_date_str = ret_val["end_date"].get<std::string>();
            url = ret_val["ret_url"].get<std::string>();
            auto end_date = boost_ptime_from_string(end_date_str);
            auto now = boost::posix_time::second_clock::local_time();

            if(end_date > now) {
                json pt {
                    {"1name", ""},
                    {"2apps_count", ""},
                    {"3data_chunks", ""}, 
                    {"4raw_size", ""}, 
                    {"5decompress_size", ""},
                    {"6response_time", ""},
                };

                pt_list.emplace_back(pt);
                pt_list.emplace_back(pt);
                LOG(INFO) << "Met end date, break..." << "\n";
                break;
            }
        }
    }

    auto rs_csv_path = "../result/result_async.csv";
    auto df = df_op::convert_json_to_df(pt_list, {});
    df_op::write_to_csv(df, rs_csv_path);
}
