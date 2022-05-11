#ifndef _FREDRIC_BEANS_H_
#define _FREDRIC_BEANS_H_

#include "json/json.hpp"

#include <map>
#include <string>
#include <vector>

using json = nlohmann::json;

struct RetentionValue {
    std::string granularity;
    std::map<std::string, std::string> mapping;
    std::vector<int> range_list;
};

struct ReqResult {
    bool status{false}; 
    std::string res;
    float avg_time;
};

struct AsyncReqResult {
    bool status{false}; 
    json res;
    float avg_time;
};

struct AsyncConCurrResult {
    float max_time; // 最大响应时间
    float min_time; // 最小响应时间
    float avg_time; // 平均响应时间
    int total_count;  // 总次数
    int fail_count;   // 失败次数
};

struct CaseContent {
    json sync_;
    json async_;
};
extern std::vector<int> day_ls;
extern std::vector<int> week_ls;
extern std::vector<int> month_ls;

extern std::map<std::string, std::string> DimProductMapping;
extern std::map<std::string, std::string> DownloadAndRevenueMapping;
extern std::map<std::string, std::string> UsageMapping;
extern std::map<std::string, std::string> DemographicsMapping;
extern std::map<std::string, RetentionValue> RetetionMappingObject;
#endif