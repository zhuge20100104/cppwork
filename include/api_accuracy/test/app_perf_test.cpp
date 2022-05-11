#include "api_accuracy/cases/app_perf_cases.h"
#include "api_accuracy/test_cfg.h"
#include "api_accuracy/utils/req.h"
#include "api_accuracy/utils/io_util.h"
#include "api_accuracy/utils/funcs.h"
#include "api_accuracy/utils/beans.h"
#include "api_accuracy/utils/compare.h"
#include "api_accuracy/utils/data_op.h"

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

class AppPerfTests: public testing::Test {
    protected:
    static void SetUpTestCase(){
        for(auto&& case_: app_perf_pos_cases) {
            auto case_name = case_.name;
            auto case_url = case_.url;

            if(!use_file) {
                auto case_result_ = Req::make_a_api_query(case_url);
                bool write_res = IOUtil::write_file(case_name, case_result_);
                if(!write_res) {
                    // Write case result failed
                    ASSERT_TRUE(false);
                }
            }
            auto content_ = IOUtil::read_file(case_name);
            app_perf_results[case_name] = json::parse(content_);
        }
    }

    static void TearDownTestCase(){}

    static std::map<std::string, json> app_perf_results;
};

std::map<std::string, json> AppPerfTests::app_perf_results{};

TEST_F(AppPerfTests, ReadFile) {
    auto query_str = IOUtil::read_file(app_perf_pos_cases[0].name);
    LOG(INFO) << query_str << "\n";
    ASSERT_TRUE(query_str!="");
}

TEST_F(AppPerfTests, GetMapKeys) { 
    auto keys = get_map_keys(DimProductMapping);
    LOG(INFO) << keys.size() << "\n";
    ASSERT_EQ(15, keys.size());
}

TEST_F(AppPerfTests, GetMapValues) { 
    auto values = get_map_values(DimProductMapping);
    LOG(INFO) << values.size() << "\n";
    ASSERT_EQ(15, values.size());
}


TEST_F(AppPerfTests, GetApiProductFields) { 
    auto app_perf_result = app_perf_results.begin()->second;
    std::cerr << app_perf_result["start_date"] << std::endl;
    Compare c {app_perf_result};
    auto values = c.get_api_products_fields(DimProductMapping);
    ASSERT_TRUE(values.size() > 0);
}

TEST_F(AppPerfTests, JsonDumpStdVector) {
    std::string country_code = "US,CN,JP,CA";
    std::vector<std::string> results_{}; 
    pystring::split(country_code, results_, ",");
    json js = results_;
    ASSERT_EQ(4, js.size());
}

TEST_F(AppPerfTests, JsonDelInnerKey) {
    auto js_str = R"(
        {
            "person": {
                "name": "Zhangsan",
                "age": 34
            },
            "grade": 3
        }
    )";
    json js = json::parse(js_str);
    js["person"].erase("age");
    LOG(INFO) << js.dump() << "\n";
}

TEST_F(AppPerfTests, ReadQueryFileAndReplaceConsts) {
    json prod = json::parse(R"({
        "product_id": 1111,
        "market_code": "google-play",
        "start_date": "2021-01-01",
        "end_date": "2021-01-31",
        "countries": "CN,US,JP",
        "devices": "android-all,android-tv",
        "granularity": "monthly"
        })");
    auto apps_meta_query_str = read_query_file_and_replace_consts(prod, apps_meta_file);
    LOG(INFO) << apps_meta_query_str << "\n";
}

TEST_F(AppPerfTests, ReadQueryFileAndReplaceConstsAllCountries) {
    json prod = json::parse(R"({
        "product_id": 1111,
        "market_code": "google-play",
        "start_date": "2021-01-01",
        "end_date": "2021-01-31",
        "countries": "all_supported",
        "devices": "android-all,android-tv",
        "granularity": "monthly"
        })");
    auto apps_meta_query_str = read_query_file_and_replace_consts(prod, apps_meta_file);
    LOG(INFO) << apps_meta_query_str << "\n";
}


TEST_F(AppPerfTests, ParseDimProductFields) {
    auto dim_file_str = IOUtil::read_file(test_dim_parse_data_file);
    auto dim_file = json::parse(dim_file_str);
    auto dim_keys_ = get_map_values(DimProductMapping);
    auto dim_values = parse_dim_product_fields(dim_file, dim_keys_);
    auto api_values = convert_dim_values_to_api_values(dim_values, DimProductMapping);
    LOG(INFO) << api_values << "\n";
}

TEST_F(AppPerfTests, TestProductMetadata) {
    bool is_case_pass = true;
    for(auto&& case_item: app_perf_results) {
        auto app_perf_file = case_item.first;
        auto app_perf_result = case_item.second;
        auto comp_ = Compare(app_perf_result);
        auto is_value_equal = comp_.compare_api_and_www_meta_equal(DimProductMapping, apps_meta_file); 
        if(!is_value_equal) {
            LOG(ERROR) << "[" << app_perf_file  << "] test [test_product_metadata] failed!\n"; 
            is_case_pass = false;
        }
    }
    ASSERT_TRUE(is_case_pass);
}

TEST_F(AppPerfTests, GetApiValues) {
    auto app_perf_result = app_perf_results.begin()->second;
    auto comp_ = Compare(app_perf_result);
    auto api_values = comp_.get_api_values(DownloadAndRevenueMapping, "download_revenue");
    ASSERT_TRUE(api_values.size() > 0);
}

TEST_F(AppPerfTests, TestDownloadAndRevenue) {
    bool is_case_pass = true;
    for(auto&& case_item: app_perf_results) {
        auto app_perf_file = case_item.first;
        auto app_perf_result = case_item.second;
        auto comp_ = Compare(app_perf_result);
        auto is_value_equal = comp_.compare_api_and_www_equal(DownloadAndRevenueMapping, "app_performance", "download_revenue", download_and_revenue); 
        
        if(!is_value_equal) {
            LOG(ERROR) << "[" << app_perf_file  << "] test [test_download_and_revenue] failed!\n"; 
            is_case_pass = false;
        }
    }
    ASSERT_TRUE(is_case_pass);
}

TEST_F(AppPerfTests, TestUsage) {
    bool is_case_pass = true;
    for(auto&& case_item: app_perf_results) {
        auto app_perf_file = case_item.first;
        auto app_perf_result = case_item.second;
        auto comp_ = Compare(app_perf_result);
        auto is_value_equal = comp_.compare_api_and_www_equal(UsageMapping, "app_performance", "usage", usage_file); 
        
        if(!is_value_equal) {
            LOG(ERROR) << "[" << app_perf_file  << "] test [test_usage] failed!\n"; 
            is_case_pass = false;
        }
    }
    ASSERT_TRUE(is_case_pass);
}

TEST_F(AppPerfTests, TestDemographics) {
    bool is_case_pass = true;
    for(auto&& case_item: app_perf_results) {
        auto app_perf_file = case_item.first;
        auto app_perf_result = case_item.second;
        auto comp_ = Compare(app_perf_result);
        auto is_value_equal = comp_.compare_api_and_www_values_equal(
                DemographicsMapping, "demographics", {demographics_age_file, demographics_gender_file});
        if(!is_value_equal) {
            LOG(ERROR) << "[" << app_perf_file  << "] test [test_usage] failed!\n"; 
            is_case_pass = false;
        }
    }
    ASSERT_TRUE(is_case_pass);
}

TEST_F(AppPerfTests, TestRentention) {
    bool is_case_pass = true;
    for(auto&& case_item: app_perf_results) {
        auto app_perf_file = case_item.first;
        auto app_perf_result = case_item.second;
        auto comp_ = Compare(app_perf_result);
        auto is_value_equal = comp_.compare_api_and_www_retention_equal(
                RetetionMappingObject, "app_performance", "retention", retention_file);
        if(!is_value_equal) {
            LOG(ERROR) << "[" << app_perf_file  << "] test [test_usage] failed!\n"; 
            is_case_pass = false;
        }
    }
    ASSERT_TRUE(is_case_pass);
}

TEST_F(AppPerfTests, TestNoDuplicatePrimaryKey) {
    bool is_case_pass = true;
    for(auto&& case_item: app_perf_results) {
        auto app_perf_file = case_item.first;
        auto app_perf_result = case_item.second;
        data_op d_op {app_perf_result};
        auto primary_df_list = d_op.get_primary_key_list();
        for(auto&& primary_df_info: primary_df_list) {
            auto product = primary_df_info["product"];
            auto primary_df = primary_df_info["key"];
            if(is_df_duplicate(primary_df)) {
                LOG(ERROR) << "[" << app_perf_file << "] test [test_no_duplicate_primary_key] failed!";
                LOG(ERROR) << product.dump();
                is_case_pass = false;
            }
        }
    }
    ASSERT_TRUE(is_case_pass);
}

TEST_F(AppPerfTests, TimestampToUtcTime) {
    auto time_ = timestamp_to_utc_time(1630800000000);
    LOG(INFO) << time_ << "\n";
    ASSERT_EQ("2021-09-05", time_);
    auto time_stamp = utc_timestamp_from_string("2021-09-05");
    LOG(INFO) << time_stamp << "\n";
    ASSERT_EQ(1630800000, time_stamp);
}

TEST_F(AppPerfTests, GetIthDay) {
    auto date_ = get_ith_day("2020-01-01", 10);
    LOG(ERROR) << date_ << "\n";
    ASSERT_EQ("2020-01-11", date_);
}

TEST_F(AppPerfTests, GetIthWeek) {
    auto date_ = get_ith_week("2020-01-01", 1);
    LOG(ERROR) << date_ << "\n";
    ASSERT_EQ("2020-01-08", date_);
}

TEST_F(AppPerfTests, GetIthMonth) {
    auto date_ = get_ith_month("2020-01-01", 3);
    LOG(ERROR) << date_ << "\n";
    ASSERT_EQ("2020-03-31", date_);
}






