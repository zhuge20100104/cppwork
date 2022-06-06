#include "api_accuracy/utils/funcs.h"

#include <pystring/pystring.h>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <algorithm>
#include <cstddef>
#include <ctime>
#include <locale>
#include <iomanip>
#include <sstream>
#include <math.h> 
#include <regex>

#include "api_accuracy/utils/io_util.h"
#include "df/df.h"
#include "glog/logging.h"

std::vector<std::string> get_map_keys(
    const std::map<std::string, std::string>& field_mapping) {
    std::vector<std::string> keys{};
    std::for_each(field_mapping.begin(), field_mapping.end(),
                  [&keys](const auto& item) { keys.push_back(item.first); });
    return keys;
}

std::vector<std::string> get_map_values(
    const std::map<std::string, std::string>& field_mapping) {
    std::vector<std::string> values{};
    std::for_each(
        field_mapping.begin(), field_mapping.end(),
        [&values](const auto& item) { values.push_back(item.second); });
    return values;
}

std::string read_query_file_and_replace_consts(
    const json& prod, const std::string& www_query_file_name) {
    auto product_id = prod["product_id"].get<int64_t>();
    auto market_code = prod["market_code"].get<std::string>();
    auto start_date = prod["start_date"].get<std::string>();
    auto end_date = prod["end_date"].get<std::string>();
    auto country_code = prod["countries"].get<std::string>();
    auto device_code = prod["devices"].get<std::string>();
    auto granularity = prod["granularity"].get<std::string>();

    auto file_content = IOUtil::read_file(www_query_file_name);

    file_content = pystring::replace(file_content, "${product_id}",
                                     std::to_string(product_id));
    file_content =
        pystring::replace(file_content, "${market_code}", market_code);
    file_content = pystring::replace(file_content, "${start_date}", start_date);
    file_content = pystring::replace(file_content, "${end_date}", end_date);
    std::vector<std::string> country_list{};
    pystring::split(country_code, country_list, ",");
    json country_js = country_list;
    file_content =
        pystring::replace(file_content, "${country_code}", country_js.dump());
    file_content =
        pystring::replace(file_content, "${granularity}", granularity);

    if (country_list[0] == "all_supported") {
        auto content_js = json::parse(file_content);
        content_js["filters"].erase("country_code");
        file_content = content_js.dump();
    }

    std::vector<std::string> device_list{};
    pystring::split(device_code, device_list, ",");
    if (device_list[0] != "all_supported") {
        auto content_js = json::parse(file_content);
        content_js["filters"]["device_code"] = {{"in", device_list}};
        file_content = content_js.dump();
    }

    return file_content;
}

json parse_dim_product_fields(const json& result_json,
                              const std::vector<std::string>& dim_keys_) {
    json values;
    auto facets = result_json["data"]["facets"];
    auto dims = result_json["data"]["dimensions"];
    for (auto&& facet_ : facets) {
        json value;
        for (auto&& dim_key_ : dim_keys_) {
            if (dim_key_.find("/") == std::string::npos) {
                value[dim_key_] = facet_[dim_key_];
            } else {
                json tmp_val;
                std::string tmp_key = "";
                std::vector<std::string> one_dim_keys{};
                pystring::split(dim_key_, one_dim_keys, "/");
                for (int i = 0; i < one_dim_keys.size(); ++i) {
                    if (i == 0) {
                        tmp_key = one_dim_keys[0];
                        if (!facet_[tmp_key].is_null()) {
                            tmp_val =
                                std::to_string(facet_[tmp_key].get<int64_t>());
                        } else {
                            break;
                        }
                    } else {
                        for (auto &&begin = dims.begin(), end = dims.end();
                             begin != end; ++begin) {
                            auto in_dim_key = begin.key();
                            auto in_dim_val = begin.value();

                            if (one_dim_keys[i - 1] == in_dim_key) {
                                for (auto &&ii_begin = in_dim_val.begin(),
                                          ii_end = in_dim_val.end();
                                     ii_begin != ii_end; ++ii_begin) {
                                    auto ii_dim_key = ii_begin.key();
                                    auto ii_dim_val = ii_begin.value();
                                    if (ii_dim_key ==
                                        tmp_val.get<std::string>()) {
                                        if (i == (one_dim_keys.size() - 1)) {
                                            tmp_val =
                                                ii_dim_val[one_dim_keys[i]];
                                        } else {
                                            if (!ii_dim_val[one_dim_keys[i]]
                                                     .is_null()) {
                                                tmp_val = std::to_string(
                                                    ii_dim_val[one_dim_keys[i]]
                                                        .get<int64_t>());
                                            } else {
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                value[dim_key_] = tmp_val;
            }
        }
        values.emplace_back(std::move(value));
    }
    return std::move(values);
}

json convert_dim_values_to_api_values(
    const json& values,
    const std::map<std::string, std::string>& api_dim_mapping) {
    json new_values;
    for (auto&& value : values) {
        json new_value;
        for (auto&& api_dim_item : api_dim_mapping) {
            auto api_key = api_dim_item.first;
            auto dim_key = api_dim_item.second;
            new_value[api_key] = value[dim_key];
        }
        new_values.emplace_back(std::move(new_value));
    }
    return std::move(new_values);
}

bool find_diff_and_save_f(const json& values_, const json& act_www_values_,
                          const std::string& api_data_field_name) {
    std::vector<std::string> pri_keys_{};
    auto df1 = df_op::convert_json_to_df(values_, pri_keys_);
    auto df2 = df_op::convert_json_to_df(act_www_values_, pri_keys_);
    std::string res_csv_path = "../result/" + api_data_field_name + "_res.csv";
    if (values_.size() == 0 && act_www_values_.size() == 0) {
        return false;
    } else if (values_.size() == 0 && act_www_values_.size() != 0) {
        df_op::write_to_csv(df2, res_csv_path);
        return true;
    } else if (values_.size() != 0 && act_www_values_.size() == 0) {
        df_op::write_to_csv(df1, res_csv_path);
        return true;
    } else {
        auto df3 =
            df1.concat<decltype(df2), json>(df2, concat_policy::all_columns);
        std::vector<std::string> keys_{Keys};
        auto df4 = df_op::remove_duplicate(df3, keys_);
        auto df_rows = df4.shape().first;
        if (df_rows == 0) {
            return false;
        }

        df_op::write_to_csv(df3, res_csv_path);
        return true;
    }
}

bool find_diff_and_save_f_for_async(const json& values_, const json& act_www_values_, const std::string& api_data_field_name) {
    std::vector<std::string> pri_keys_{};
    auto df1 = df_op::convert_json_to_df(values_, pri_keys_);
    auto df2 = df_op::convert_json_to_df(act_www_values_, pri_keys_);
    std::string res_csv_path = "../result/" + api_data_field_name + "_res.csv";
    if (values_.size() == 0 && act_www_values_.size() == 0) {
        return false;
    } else if (values_.size() == 0 && act_www_values_.size() != 0) {
        df_op::write_to_csv(df2, res_csv_path);
        return true;
    } else if (values_.size() != 0 && act_www_values_.size() == 0) {
        df_op::write_to_csv(df1, res_csv_path);
        return true;
    } else { 
        auto df1_row = df1.shape().first;
        auto df2_row = df2.shape().first;
        auto max_len = std::max(df1_row, df2_row);
        auto min_len = std::min(df1_row, df2_row);

        auto df3 =
            df1.concat<decltype(df2), json>(df2, concat_policy::all_columns);
        std::vector<std::string> keys_{Keys};
        auto df4 = df_op::remove_duplicate(df3, keys_);
        auto df_rows = df4.shape().first;

        df_op::write_to_csv(df3, res_csv_path);

        if(df_rows == (max_len - min_len)) {
            return false;
        } else {
            return true;
        }
    }
}

bool is_df_duplicate(const json& values_) {
    if(values_.size() == 0) {
        return false;
    }

    std::vector<std::string> pri_keys_{};
    auto df1 = df_op::convert_json_to_df(values_, pri_keys_);
    
    std::vector<std::string> keys_{Keys};
    auto df2 = df_op::remove_duplicate(df1, keys_);
    auto df1_row = df1.shape().first;
    auto df2_row = df2.shape().first;

    if(df1_row != df2_row) {
        return true;
    }
    return false;
}

std::string timestamp_to_utc_time(const uint64_t& timestamp_) {
    long gmt_time = (long)((double)timestamp_ / (double)1000);
    auto time_ = boost::posix_time::from_time_t(gmt_time);
    auto date_time_str = boost::posix_time::to_iso_extended_string(time_);
    std::vector<std::string> dates_;
    pystring::split(date_time_str, dates_, "T");
    return dates_[0];
}

// Return timestamp as seconds
time_t utc_timestamp_from_string(const std::string& date_str) {
    std::stringstream ios_extended_ss {};
    ios_extended_ss << date_str << "T" << "00:00:00";
    auto time_ = boost::posix_time::from_iso_extended_string(ios_extended_ss.str());
    auto time_stamp = boost::posix_time::to_time_t(time_);
    return time_stamp;
}

// Return boost::posix_time::ptime object
boost::posix_time::ptime boost_ptime_from_string(const std::string& date_str) {
    std::stringstream ios_extended_ss {};
    ios_extended_ss << date_str << "T" << "00:00:00";
    auto time_ = boost::posix_time::from_iso_extended_string(ios_extended_ss.str());
    return std::move(time_);
}


std::string _convert_boost_date_to_str(const boost::gregorian::date& d) {
    std::stringstream ss;
    ss << d.year() << "-";
    int month = (int)(d.month());
    if(month < 10) {
        ss << "0";
    }
    ss << month << "-";
    int day = d.day();
    if(day < 10) {
        ss << "0";
    }
    ss << day;
    return std::move(ss.str());
}

std::string get_ith_day(const std::string& date_str, const int i) {
    std::vector<std::string> dates_;
    pystring::split(date_str, dates_, "-");
    int year = std::atoi(dates_[0].c_str());
    int month = std::atoi(dates_[1].c_str());
    int day = std::atoi(dates_[2].c_str());
    boost::gregorian::date d(year, month, day);
    boost::gregorian::date_duration dd(i * 1);
    d += dd;
    auto ret_date_str = _convert_boost_date_to_str(d);
    return std::move(ret_date_str);
}

std::string get_ith_week(const std::string& date_str, const int i) {
    std::vector<std::string> dates_;
    pystring::split(date_str, dates_, "-");
    int year = std::atoi(dates_[0].c_str());
    int month = std::atoi(dates_[1].c_str());
    int day = std::atoi(dates_[2].c_str());
    boost::gregorian::date d(year, month, day);
    boost::gregorian::weeks_duration dd(i * 1);
    d += dd;
    auto ret_date_str = _convert_boost_date_to_str(d);
    return std::move(ret_date_str);
}

std::string get_ith_month(const std::string& date_str, const int i) {
    std::vector<std::string> dates_;
    pystring::split(date_str, dates_, "-");
    int year = std::atoi(dates_[0].c_str());
    int month = std::atoi(dates_[1].c_str());
    int day = std::atoi(dates_[2].c_str());
    boost::gregorian::date d(year, month, day);
    boost::gregorian::date end_d = d.end_of_month();
    for(int idx = 0; idx < i-1; ++idx) {
        end_d += boost::gregorian::date_duration(1);
        end_d = end_d.end_of_month();
    }
    
    auto ret_date_str = _convert_boost_date_to_str(end_d);
    return std::move(ret_date_str);
}

float get_float_fraction(float number) {
    float int_part;
    float fractpart = modf (number, &int_part);
    return fractpart;
}

json parse_start_date_and_end_date_from_url(const std::string& url) {
    std::regex start_pattern(R"(start_date=(\d{4}-\d{1,2}-\d{1,2}))"); 
    std::regex end_pattern(R"(end_date=(\d{4}-\d{1,2}-\d{1,2}))"); 
    std::smatch start_date_match;
    std::smatch end_date_match;
    std::regex_search(url, start_date_match, start_pattern);
    std::regex_search(url, end_date_match, end_pattern);
    auto start_date = start_date_match[0];
    auto end_date = end_date_match[0];
    json date_range {
        {"start_date", start_date},
        {"end_date", end_date}
    };

    LOG(INFO) << date_range << "\n";
    return std::move(date_range);
}

std::string replace_end_date_with_given_date(const std::string& given_date, const std::string& url) {
    std::regex end_pattern(R"(end_date=(\d{4}-\d{1,2}-\d{1,2}))");

    std::stringstream given_date_ss;
    given_date_ss << "end_date=" << given_date;
    auto given_date_str = given_date_ss.str();

    std::string new_url = std::regex_replace(url, end_pattern, given_date_str);
    return std::move(new_url);
}

json adjust_req_url_date(const std::string& url, int i) {
    auto d_range = parse_start_date_and_end_date_from_url(url);
    auto start_date_str = d_range["start_date"].get<std::string>();
    std::vector<std::string> start_date_vec;
    pystring::split(start_date_str, start_date_vec, "=");
    std::string end_date;
    if(url.find("daily") != std::string::npos) {
        end_date =  get_ith_day(start_date_vec[1], i);
    } else if(url.find("monthly") != std::string::npos) {
        end_date =  get_ith_month(start_date_vec[1], i);
    } else if(url.find("weekly") != std::string::npos) {
        end_date =  get_ith_week(start_date_vec[1], i);
    }
    auto ret_url = replace_end_date_with_given_date(end_date, url);

    json ret_val {
        {"end_date", end_date}, 
        {"ret_url", ret_url}
    };
    return std::move(ret_val);
}
   