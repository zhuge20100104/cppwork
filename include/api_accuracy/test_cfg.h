#ifndef _FREDRIC_TEST_CFG_H_
#define _FREDRIC_TEST_CFG_H_

#include <string>
#include <map>
#include <vector>

extern std::string v2_query_path;
extern int max_compare_count;

// Max async result timeout in seconds
extern int max_async_timeout;
extern int sleep_interval;

// Performance Testing的retry次数
extern int perf_retry_count;

// 异步并发的个数
extern int async_concurr_count;

extern std::string www_host;
extern std::string api_host;
extern std::string async_api_host;
extern std::string report_path;

extern std::string www_company_path;

extern std::map<std::string, std::string> www_headers;

extern std::map<std::string, std::string> api_headers;
extern std::map<std::string, std::string> async_api_headers;

extern std::map<std::string, std::string> zipped_api_headers;
extern bool use_file;

// App Performance related json files

extern std::string apps_meta_file;
extern std::string download_and_revenue;
extern std::string usage_file;
extern std::string demographics_age_file;
extern std::string demographics_gender_file;
extern std::string retention_file;

extern std::string test_dim_parse_data_file;
extern std::vector<std::string> common_keys;

#endif