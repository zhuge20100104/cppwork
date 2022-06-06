#include <glog/logging.h>
#include <gtest/gtest.h>

#include "api_accuracy/cases/app_perf_cases.h"
#include "api_accuracy/utils/req.h"
#include "death_handler/death_handler.h"
#include "json/json.hpp"

using json = nlohmann::json;

int main(int argc, char** argv) {
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 2;

    Debug::DeathHandler dh;

    google::InitGoogleLogging("./logs.log");
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

class AppPerfNegTests : public testing::Test {
   protected:
    static void SetUpTestCase() { negative_cases = app_perf_neg_cases; }

    static void TearDownTestCase() {}

    static std::vector<Case> negative_cases;
};

std::vector<Case> AppPerfNegTests::negative_cases;

TEST_F(AppPerfNegTests, TestNegativeCases) {
    bool is_case_pass = true;
    for (auto&& negative_case : negative_cases) {
        auto name = negative_case.name;
        auto url = negative_case.url;
        auto expect_code = negative_case.expect_code;
        auto query_result_str = Req::make_a_api_query(url);
        auto res = json::parse(query_result_str);
        auto code_it = res.find("code");
        if (code_it != res.end()) {
            // {
            //             "code": 400,
            //             "error": "Input error: PLEASE SPECIFY ONE OF THE
            //             PARAMETERS: [company_id, apps]."
            // }
            if (res["code"] != expect_code) {
                LOG(ERROR) << "[" << url << "] test [" << name << "] failed!\n";
                is_case_pass = false;
            }
        } else {
            //  {
            //             "errors": [
            //                 {
            //                     "code": "400",
            //                     "message": "AAFlaskException: Missing query
            //                     parameter 'start_date'"
            //                 }
            //             ]
            // }

            auto code_str = res["errors"][0]["code"].get<std::string>();
            auto code_ = std::atoi(code_str.c_str());
            if (code_ != expect_code) {
                LOG(ERROR) << "[" << url << "] test [" << name << "] failed!\n";
                is_case_pass = false;
            }
        }
    }
    ASSERT_TRUE(is_case_pass);
}
