#ifndef _FREDRIC_COMPARE_H_
#define _FREDRIC_COMPARE_H_

#include "api_accuracy/utils/beans.h"

#include <json/json.hpp>

#include <map>
#include <string>

using json = nlohmann::json;

struct Compare {
    Compare(const json& app_perf_result);

    json get_api_products_fields(const std::map<std::string, std::string>& field_mapping);

    json get_www_product_fields(const json& prod, const std::string& www_request_file_name, const std::map<std::string, std::string>& field_mapping);

    bool compare_api_and_www_meta_equal(const std::map<std::string, std::string>& field_mappings, const std::string& www_query_file);

    bool compare_api_and_www_equal(const std::map<std::string, std::string>& field_mappings, const std::string& api_data_field_name, const std::string& result_file_name, const std::string& www_query_file);

    bool compare_api_and_www_values_equal(const std::map<std::string, std::string>& field_mappings, const std::string& api_data_field_name, const std::vector<std::string>& www_query_file_list);
    
    bool compare_api_and_www_retention_equal(const std::map<std::string, RetentionValue>& field_mappings, const std::string& api_data_field_name, const std::string& result_file_name,  const std::string& www_query_file);

    json get_api_values(const std::map<std::string, std::string>& field_mappings, const std::string& data_field_name);

    json get_one_www_value(const json& prod, const std::string& www_request_file_name, const std::map<std::string, std::string>& field_mappings);

    json get_retention_www_values(const json& prod, const std::string& www_request_file_name, const RetentionValue& rent_value);
    
    const json&  app_perf_result_;
};
#endif