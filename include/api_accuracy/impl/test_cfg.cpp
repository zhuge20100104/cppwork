#include "api_accuracy/test_cfg.h"

std::string api_host = "api.appannie.com";
std::string async_api_host = "api.appannie.com";
std::string report_path = "/v1.3/portfolio/fetch-data?report_id=";

std::string www_host = "api2.appannie.com";

std::string v2_query_path = "/v2/query";
int max_compare_count = 10;

int max_async_timeout = 60;
int sleep_interval = 10;

int perf_retry_count = 1;

// TODO: modify back concurr count: 20 threads for async concurr
int async_concurr_count = 30;

std::map<std::string, std::string> www_headers{
    {"Content-Type", "application/json"}
};

std::map<std::string, std::string> api_headers{
    {"Accept-Encoding", "gzip"},
    {"Authorization", "Bearer b63a75acb8af62528d966a73b1af914d8531496c"},
    {"Content-Type", "application/json"}
};

std::map<std::string, std::string> async_api_headers{
    {"Accept-Encoding", "gzip"},
    {"Authorization", "Bearer b63a75acb8af62528d966a73b1af914d8531496c"},
     {"Content-Type", "application/json"}
};

std::map<std::string, std::string>  zipped_api_headers {
    {"Authorization", "Bearer b63a75acb8af62528d966a73b1af914d8531496c"},
    {"Content-Type", "application/json"}
};

bool use_file = false;

std::string apps_meta_file = "../datas/app_perf/apps_meta_data.json";
std::string test_dim_parse_data_file = "../datas/app_perf/test_dim_parse_data.json";
std::string download_and_revenue = "../datas/app_perf/download_and_revenue.json"; 
std::string usage_file = "../datas/app_perf/usage.json";
std::string demographics_age_file = "../datas/app_perf/demographics_age.json";
std::string demographics_gender_file = "../datas/app_perf/demographics_gender.json";
std::string retention_file = "../datas/app_perf/retention.json";

std::vector<std::string> common_keys {"date", "country_code", "device_code"};