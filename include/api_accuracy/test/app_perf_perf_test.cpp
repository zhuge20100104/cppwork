#include "api_accuracy/cases/app_perf_cases.h"
#include "api_accuracy/test_cfg.h"
#include "api_accuracy/utils/req.h"
#include "api_accuracy/utils/io_util.h"
#include "api_accuracy/utils/funcs.h"
#include "api_accuracy/utils/beans.h"
#include "api_accuracy/utils/compare.h"
#include "api_accuracy/utils/decorator.hpp"
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


class AppPerfPerfTests : public testing::Test {
   protected:
    static void SetUpTestCase() { perf_cases = app_perf_perf_cases; }

    static void TearDownTestCase() {}

    static std::vector<Case> perf_cases;
};

std::vector<Case> AppPerfPerfTests::perf_cases{};

TEST_F(AppPerfPerfTests, ParseStartDateAndEndDateFromUrl) {
    const std::string url = "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=monthly&start_date=2020-01-01&end_date=2020-03-31&countries=US,CN,JP,GB";

    auto date_range = parse_start_date_and_end_date_from_url(url);
    auto start_date = date_range["start_date"].get<std::string>();
    auto end_date = date_range["end_date"].get<std::string>();
    LOG(INFO) << start_date << "\n";
    LOG(INFO) << end_date << "\n";
    ASSERT_EQ("start_date=2020-01-01", start_date);
    ASSERT_EQ("end_date=2020-03-31", end_date);
}

TEST_F(AppPerfPerfTests, ReplaceEndDateWithGivenDate) {
    const std::string url = "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=monthly&start_date=2020-01-01&end_date=2020-03-31&countries=US,CN,JP,GB";
    const std::string given_date = "2020-05-31";
    auto new_url = replace_end_date_with_given_date(given_date, url);
    LOG(INFO) << new_url << "\n"; 
    auto expect_url = "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=monthly&start_date=2020-01-01&end_date=2020-05-31&countries=US,CN,JP,GB";
    ASSERT_EQ(expect_url, new_url);
}

TEST_F(AppPerfPerfTests, TestPerfCases) {
    json pt_list;
    auto req_test_func = make_decorator(Req::make_a_api_query); 

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
                LOG(INFO) << "Met 521 error, break..." << "\n";
                break;
            }
            auto res_content = req_result.res;
            auto response_time = req_result.avg_time;
            auto zipped_content = Req::make_a_zipped_query(url);

            auto raw_size = (float)(zipped_content.size()) / (float)(1024);
            auto decompress_size = (float)(res_content.size()) / (float)(1024);
        
            LOG(INFO) << "Raw size: " << raw_size << "\n";
            LOG(INFO) << "Decompressed size:" << decompress_size << "\n";
            auto res_js = json::parse(res_content);
            auto d_op = data_op(res_js);
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

    auto rs_csv_path = "../result/result.csv";
    auto df = df_op::convert_json_to_df(pt_list, {});
    df_op::write_to_csv(df, rs_csv_path);
}
