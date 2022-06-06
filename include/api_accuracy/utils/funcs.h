#ifndef _FREDRIC_FUNCS_H_
#define _FREDRIC_FUNCS_H_

#include "json/json.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>

#include <vector>
#include <string>
#include <map>

using json = nlohmann::json;

std::vector<std::string> get_map_keys(const std::map<std::string, std::string>& field_mapping);
std::vector<std::string> get_map_values(const std::map<std::string, std::string>& field_mapping);
std::string read_query_file_and_replace_consts(const json& prod, const std::string& www_query_file_name);
json parse_dim_product_fields(const json& result_json, const std::vector<std::string>& dim_keys_);
json convert_dim_values_to_api_values(const json& values, const std::map<std::string, std::string>& api_dim_mapping);
bool find_diff_and_save_f(const json& values_, const json& act_www_values_, const std::string& api_data_field_name);
bool find_diff_and_save_f_for_async(const json& values_, const json& act_www_values_, const std::string& api_data_field_name);
bool is_df_duplicate(const json& values_);

std::string timestamp_to_utc_time(const uint64_t& timestamp_);
time_t utc_timestamp_from_string(const std::string& date_str);
boost::posix_time::ptime boost_ptime_from_string(const std::string& date_str);

std::string get_ith_day(const std::string& date_str, const int i);
std::string get_ith_week(const std::string& date_str, const int i);
std::string get_ith_month(const std::string& date_str, const int i);

float get_float_fraction(float number);

json parse_start_date_and_end_date_from_url(const std::string& url);

std::string replace_end_date_with_given_date(const std::string& given_date, const std::string& url);

json adjust_req_url_date(const std::string& url, int i);
#endif