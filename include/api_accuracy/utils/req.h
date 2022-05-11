#ifndef _FREDRIC_REQ_H_
#define _FREDRIC_REQ_H_

#include "api_accuracy/utils/beans.h"

#include <string>
#include "json/json.hpp"

using json = nlohmann::json;

struct Req {
    static std::string make_a_www_query(const std::string& path, const std::string& body);
    static std::string make_a_api_query(const std::string& path); 
    static std::string make_a_async_api_query(const std::string& path);
    static std::string make_a_zipped_query(const std::string& path);
    static json make_a_async_api_query_and_get_report_url(const std::string& path);
    static void make_a_async_api_query_and_get_report_url(const std::string& path, json &res);
    static std::string make_a_async_zipped_query(const std::string& report_url);
};
#endif