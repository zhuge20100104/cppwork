#include <glog/logging.h>
#include <gtest/gtest.h>
#include "death_handler/death_handler.h"
#include "json/json.hpp"

#include "http1/http_util.h"
#include "pystring/pystring.h"
#include "http1/url_parse.h"

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



GTEST_TEST(HttpTests, TestGetFile) {
    auto res = http_util::get_file("cn.bing.com", "/", "bing.html");

    ASSERT_TRUE(res);
}

GTEST_TEST(HttpTests, TestGetGzipFile) {
   
   std::map<std::string, std::string> api_headers{
        {"Authorization", "Bearer 0fde144b7a220b7c76fe3077b01c1e231fe738fe"}
    };

    url_parse parse_1 {"https://api2.appannie.com/v2/bulk/data?name=metrics/app_store_ratings_product_level/all/all/daily/2019-05-01/data.10000001.20191031.3.csv.gz&signature=5974f32e1712c9880e74527745bae409"};
    parse_1.parse_host_and_path();
    std::string host = parse_1.get_host();
    std::string path = parse_1.get_path();

    std::string result_name = "./data.10000001.20191031.3.csv.gz";

    auto redirect_url = http_util::get_redirect_url(host, path, api_headers);

    std::cerr << "Redirect url: " << redirect_url << std::endl;
    url_parse parse_2 {redirect_url};
    parse_2.parse_host_and_path();
    host = parse_2.get_host();
    path = parse_2.get_path();

    auto download_res = http_util::get_file(host, path, result_name);
    ASSERT_TRUE(download_res);
}

GTEST_TEST(HttpTests, TestGetStr) {
    std::string host = "api.appannie.com";
    std::string path =
        "/v1.3/intelligence/apps/google-play/"
        "ranking?countries=BH&categories=OVERALL&device=android&start_date="
        "2021-08-01";
    std::map<std::string, std::string> headers{
        {"Authorization", "Bearer 6a7a558ecdc18f110087c9a38b4df28de019f083"}};
    std::string result{};
    bool get_str_res = http_util::get_str(host, path, headers, result);
    ASSERT_EQ(true, get_str_res);
    ASSERT_TRUE(result.size() > 0);
}

GTEST_TEST(HttpTests, GetZippedStr) {
    std::string host = "api.appannie.com";
    std::string path =
        "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=daily&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB";
    std::map<std::string, std::string> headers{
        {"Authorization", "Bearer cb5685cc45423934256c893cff23408b1a50208c"}
    };
    std::string result{};
    bool get_str_res = http_util::get_zipped_str(host, path, headers, result);
    std::cerr << result << std::endl;
    ASSERT_EQ(true, get_str_res);
    ASSERT_TRUE(result.size() > 0);
}

const std::string BodyTemplate = R"({"facets":["store_product_rank_paid__aggr","value_change(store_product_rank_paid__aggr)__aggr"],"filters":{"value_change":{"span_value":1,"span_unit":"PERIOD"},"granularity":{"equal":"daily"},"date":{"equal":"2021-08-11"},"country_code":{"equal":"{COUNTRY_CODE}"},"device_code":{"equal":"android-all"},"category_id":{"equal":400000}},"breakdowns":{"product_id":{}},"pagination":{"offset":0,"limit":100},"order_by":[{"name":"store_product_rank_paid__aggr","order":"asc"}],"fields":{"product_id":{"fields":["name","icon_url","publisher_id","market_code","device_code","vertical_code","is_sensitive","status","category_id"],"category_id":{"fields":["name"]},"publisher_id":{"fields":["name","company_id"],"company_id":{"fields":["name","country_code"]}}}}})";

GTEST_TEST(PostTests, PostJson) {
    std::string host = "api2.appannie.com";
    std::string path =
        R"(/v2/query)";
    std::map<std::string, std::string> headers{
       {"Authorization", "Bearer 501b0ae76f7732aa7335564e7795ad9bb8ffe493"},
    {"Content-Type", "application/json"}};

    std::string body_str = pystring::replace(BodyTemplate, "{COUNTRY_CODE}", "BD");
    std::string result{};
    bool get_str_res = http_util::post_and_get_str(host, path, headers, body_str, result);
    std::cerr << result << std::endl;
    ASSERT_EQ(true, get_str_res);
}

