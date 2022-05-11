#include "http/http_util.h"
#include "pystring/pystring.h"
#include "http/url_parse.h"
#include <gtest/gtest.h>


#include <fstream>
#include <sstream>

GTEST_TEST(GetTests, GetAWebPage) {
    std::string url = "https://cn.bing.com";
    std::string path = "/";
    std::string result_name = "./1.html";
    bool download_res = HttpUtil::get(url, path, result_name);
    ASSERT_TRUE(download_res);

    std::ifstream ifs{result_name};
    std::ostringstream oss;
    oss << ifs.rdbuf();
    std::string page_content = oss.str();
    ASSERT_TRUE(page_content.find("bing") != std::string::npos);
}

GTEST_TEST(GetTests, GetAPngFile) {
    std::string host = "static-s.aa-cdn.net";
    std::string path = "/img/ios/284882215/41fa57b3f8af3dcd4793e532e4bae114";
    std::string result_name = "1.png";
    bool download_res = HttpUtil::get_file(host, path, result_name);
    ASSERT_TRUE(download_res);
}


GTEST_TEST(GetTests, GetBingStr) {
    std::string host = "cn.bing.com";
    std::string path = "/";
    std::map<std::string, std::string> headers{};
    std::string result{};
    bool get_str_res = HttpUtil::get_str(host, path, headers, result);
    ASSERT_EQ(true, get_str_res);
    ASSERT_TRUE(result.size() > 0);
}

GTEST_TEST(GetTests, GetStr) {
    std::string host = "api.appannie.com";
    std::string path =
        "/v1.3/intelligence/apps/google-play/"
        "ranking?countries=BH&categories=OVERALL&device=android&start_date="
        "2021-08-01";
    std::map<std::string, std::string> headers{
        {"Authorization", "Bearer 6a7a558ecdc18f110087c9a38b4df28de019f083"}};
    std::string result{};
    bool get_str_res = HttpUtil::get_str(host, path, headers, result);
    ASSERT_EQ(true, get_str_res);
    ASSERT_TRUE(result.size() > 0);
}

GTEST_TEST(GetTests, GetZippedStr) {
    std::string host = "api.appannie.com";
    std::string path =
        "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=daily&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB";
    std::map<std::string, std::string> headers{
        {"Authorization", "Bearer cb5685cc45423934256c893cff23408b1a50208c"}
    };
    std::string result{};
    bool get_str_res = HttpUtil::get_zipped_str(host, path, headers, result);
    std::cerr << result << std::endl;
    ASSERT_EQ(true, get_str_res);
    ASSERT_TRUE(result.size() > 0);
}


    const std::string BodyTemplate = R"({"facets":["store_product_rank_paid__aggr","value_change(store_product_rank_paid__aggr)__aggr"],"filters":{"value_change":{"span_value":1,"span_unit":"PERIOD"},"granularity":{"equal":"daily"},"date":{"equal":"2021-08-11"},"country_code":{"equal":"{COUNTRY_CODE}"},"device_code":{"equal":"android-all"},"category_id":{"equal":400000}},"breakdowns":{"product_id":{}},"pagination":{"offset":0,"limit":100},"order_by":[{"name":"store_product_rank_paid__aggr","order":"asc"}],"fields":{"product_id":{"fields":["name","icon_url","publisher_id","market_code","device_code","vertical_code","is_sensitive","status","category_id"],"category_id":{"fields":["name"]},"publisher_id":{"fields":["name","company_id"],"company_id":{"fields":["name","country_code"]}}}}})";

GTEST_TEST(PostTests, PostJson) {
    std::string host = "tai.appannie.com";
    std::string path =
        R"(/ajax/v2/query?query_identifier=table_change%28top_apps%24gp_overview_paid%29)";
    std::map<std::string, std::string> headers{
        {"Authorization", "Bearer ffe525b4133e6d40412a819dba342f301ffb9889"},
        {"pragma", "no-cache"},
        {"cache-control", "no-cache"},
        {"sec-ch-ua", R"(Chromium";v="92", " Not A;Brand";v="99", "Microsoft Edge";v="92")"},
        {"user-agent", R"(Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/92.0.4515.131 Safari/537.36 Edg/92.0.902.73)"},
        {"disable-udw-reader-sql-cache", "1"}};

    std::string body_str = pystring::replace(BodyTemplate, "{COUNTRY_CODE}", "BD");
    std::string result{};
    bool get_str_res = HttpUtil::post_and_get_str(host, path, headers, body_str, result);
    ASSERT_EQ(true, get_str_res);
}

GTEST_TEST(GetTests, GetGPStore) {
    std::string host = "play.google.com";
    std::string path = "/store/apps/details?id=com.facebook.katana";
    std::string result_name = "./play.html";
    bool download_res = HttpUtil::get_file(host, path, result_name);
    ASSERT_TRUE(download_res);
}

GTEST_TEST(GetTests, GetGZFile) {
    std::map<std::string, std::string> api_headers{
        {"Authorization", "Bearer 0fde144b7a220b7c76fe3077b01c1e231fe738fe"}
    };

    url_parse parse_1 {"https://api2.appannie.com/v2/bulk/data?name=metrics/app_store_ratings_product_level/all/all/daily/2019-05-01/data.10000001.20191031.3.csv.gz&signature=5974f32e1712c9880e74527745bae409"};
    parse_1.parse_host_and_path();
    std::string host = parse_1.get_host();
    std::string path = parse_1.get_path();

    std::string result_name = "./data.10000001.20191031.3.csv.gz";

    auto redirect_url = HttpUtil::get_redirect_url(host, path, api_headers);

    std::cerr << "Redirect url: " << redirect_url << std::endl;
    url_parse parse_2 {redirect_url};
    parse_2.parse_host_and_path();
    host = parse_2.get_host();
    path = parse_2.get_path();

    auto download_res = HttpUtil::get_file(host, path, result_name);
    ASSERT_TRUE(download_res);
}