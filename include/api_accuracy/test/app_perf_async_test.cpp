#include <glog/logging.h>
#include <gtest/gtest.h>

#include <sstream>

#include "api_accuracy/cases/app_perf_cases.h"
#include "api_accuracy/test_cfg.h"
#include "api_accuracy/utils/beans.h"
#include "api_accuracy/utils/compare.h"
#include "api_accuracy/utils/data_op.h"
#include "api_accuracy/utils/funcs.h"
#include "api_accuracy/utils/io_util.h"
#include "api_accuracy/utils/req.h"
#include "death_handler/death_handler.h"
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

class AppPerfAsyncTests : public testing::Test {
   protected:
    static void SetUpTestCase()  {
        for (auto&& case_ : app_perf_async_cases) {
            auto case_name = case_.name;
            auto case_sync_url = case_.sync_url;
            auto case_async_url = case_.async_url;
            std::stringstream sync_file_ss;
            sync_file_ss << "../datas/app_perf/" << case_name << "_sync";
            auto case_sync_file = sync_file_ss.str();

            std::stringstream async_file_ss;
            async_file_ss << "../datas/app_perf/" << case_name << "_async";
            auto case_async_file = async_file_ss.str();

            if (!use_file) {
                auto sync_result_ = Req::make_a_api_query(case_sync_url);

                bool write_res =
                    IOUtil::write_file(case_sync_file, sync_result_);
                if (!write_res) {
                    // Write case result failed
                    ASSERT_TRUE(false);
                }

                auto async_result_ =
                    Req::make_a_async_api_query(case_async_url);

                bool async_write_res =
                    IOUtil::write_file(case_async_file, async_result_);
                if (!async_write_res) {
                    // Write case result failed
                    ASSERT_TRUE(false);
                }
            }
            auto sync_cont =
                std::move(json::parse(IOUtil::read_file(case_sync_file)));
            auto async_cont =
                std::move(json::parse(IOUtil::read_file(case_async_file)));
            auto case_cont = CaseContent{sync_cont, async_cont};
            app_perf_results[case_name] = std::move(case_cont);
        }
    }

    static void TearDownTestCase() {}

    static std::map<std::string, CaseContent> app_perf_results;
};

std::map<std::string, CaseContent> AppPerfAsyncTests::app_perf_results{};

TEST_F(AppPerfAsyncTests, TestAppPerformance) {
    bool is_case_pass = true;
    for (auto&& case_item : app_perf_results) {
        auto app_perf_file = case_item.first;
        auto app_perf_result = case_item.second;
        auto sync_cont = app_perf_result.sync_;
        auto async_cont = app_perf_result.async_;

        data_op d_op(sync_cont);
        auto sync_app_perfs = d_op.get_app_performance();
        data_op async_d_op(async_cont);
        auto async_app_perfs = async_d_op.get_app_performance();
        bool has_diff = false;
        for (auto &&begin = sync_app_perfs.begin(), end = sync_app_perfs.end();
             begin != end; ++begin) {
            auto product = begin.key();
            auto sync_app_perf = begin.value();
            // skip null values
            if(sync_app_perf.is_null() || sync_app_perf.size() == 0) {
                continue;
            }

            auto async_app_perf = async_app_perfs[product];
            has_diff = find_diff_and_save_f_for_async(
                sync_app_perf, async_app_perf, "app_performance");

            if (has_diff) {
                is_case_pass = false;
                LOG(ERROR) << "[" << app_perf_file
                           << "] test [test_app_performance] failed!";
                LOG(ERROR) << "Product: =============";
                LOG(ERROR) << product;
                LOG(ERROR) << "";
                LOG(ERROR) << "Sync app Perf: ========";
                LOG(ERROR) << sync_app_perf.dump();
                LOG(ERROR) << "";
                LOG(ERROR) << "Async app perf: =======";
                LOG(ERROR) << async_app_perf.dump();
                LOG(ERROR) << "";
                break;
            }
        }
        if(has_diff) {
            break;
        }
    }
    ASSERT_TRUE(is_case_pass);
}

TEST_F(AppPerfAsyncTests, TestDemographics) {
    bool is_case_pass = true;
    for (auto&& case_item : app_perf_results) {
        auto app_perf_file = case_item.first;
        auto app_perf_result = case_item.second;
        auto sync_cont = app_perf_result.sync_;
        auto async_cont = app_perf_result.async_;

        data_op d_op(sync_cont);
        auto sync_app_perfs = d_op.get_demographics();
        data_op async_d_op(async_cont);
        auto async_app_perfs = async_d_op.get_demographics();

        bool has_diff = false;
        for (auto &&begin = sync_app_perfs.begin(), end = sync_app_perfs.end();
             begin != end; ++begin) {
            auto product = begin.key();
            auto sync_app_perf = begin.value();
            // skip null values
            if(sync_app_perf.is_null() || sync_app_perf.size() == 0) {
                continue;
            }

            auto async_app_perf = async_app_perfs[product];
            has_diff = find_diff_and_save_f_for_async(
                sync_app_perf, async_app_perf, "demographics");

            if (has_diff) {
                is_case_pass = false;
                LOG(ERROR) << "[" << app_perf_file
                           << "] test [test_demographics] failed!";
                LOG(ERROR) << "Product: =============";
                LOG(ERROR) << product;
                LOG(ERROR) << "";
                LOG(ERROR) << "Sync app Perf: ========";
                LOG(ERROR) << sync_app_perf.dump();
                LOG(ERROR) << "";
                LOG(ERROR) << "Async app perf: =======";
                LOG(ERROR) << async_app_perf.dump();
                LOG(ERROR) << "";
                break;
            }
        }
        if(has_diff) {
            break;
        }
    }
    ASSERT_TRUE(is_case_pass);
}

TEST_F(AppPerfAsyncTests, TestProductMetadata) {
    bool is_case_pass = true;
    for (auto&& case_item : app_perf_results) {
        auto app_perf_file = case_item.first;
        auto app_perf_result = case_item.second;
        auto sync_cont = app_perf_result.sync_;
        auto async_cont = app_perf_result.async_;

        data_op d_op(sync_cont);
        auto sync_app_perfs = d_op.get_product_meta_data();
        data_op async_d_op(async_cont);
        auto async_app_perfs = async_d_op.get_product_meta_data();

        auto has_diff = find_diff_and_save_f_for_async(
            sync_app_perfs, async_app_perfs, "product_metadata");
        if (has_diff) {
            LOG(ERROR) << "[" << app_perf_file
                       << "] test [test_product_metadata] failed!";
            is_case_pass = false;
        }
    }
    ASSERT_TRUE(is_case_pass);
}

TEST_F(AppPerfAsyncTests, TestJsonDeepCopy) {
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

    auto person = js["person"];
    person.erase("name");
    LOG(INFO) << person.dump() << "\n";

    LOG(INFO) << js.dump() << "\n";
    ASSERT_EQ(R"({"age":34})", person.dump());
    ASSERT_EQ(R"({"grade":3,"person":{"age":34,"name":"Zhangsan"}})",
              js.dump());
}
