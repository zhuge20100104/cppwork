#ifndef _FREDRIC_CONFIG_H_
#define _FREDRIC_CONFIG_H_

#include "query_ele.h"


#include <map>
#include <string>
#include <vector>

// HTTP服务器Host地址
const std::string Host = "tai.appannie.com";

// 所有新增加的GP支持的国家
const std::vector<std::string> GPCountries{
    "IR", "BD", "BH", "EC", "GT", "KG", "LK", "MD", "RS", "TT",
    "AM", "DZ", "BA", "GH", "BO", "BY", "LU", "DO", "HN", "KH",
    "IQ", "JM", "JO", "MO", "SI", "UZ", "MK", "NP", "MA", "PY",
    "SV", "OM", "PA", "TZ", "QA", "TN", "UY", "VE", "YE"};

// 通用的 HTTP头配置
std::map<std::string, std::string> headers{
    {"Authorization", "Bearer ffe525b4133e6d40412a819dba342f301ffb9889"},
    {"pragma", "no-cache"},
    {"cache-control", "no-cache"},
    {"X-AA-DMS-NAMESPACE", "taiaaauthorisationservice939"},
    {"sec-ch-ua",
     R"(Chromium";v="92", " Not A;Brand";v="99", "Microsoft Edge";v="92")"},
    {"user-agent",
     R"(Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/92.0.4515.131 Safari/537.36 Edg/92.0.902.73)"},
    {"disable-udw-reader-sql-cache", "1"}};

// Query的 json文件存放的位置
const std::string QueryDataPath = "../../data/";

#endif
