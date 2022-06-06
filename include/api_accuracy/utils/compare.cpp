#include "api_accuracy/utils/compare.h"
#include "api_accuracy/utils/funcs.h"
#include "api_accuracy/utils/req.h"
#include "api_accuracy/test_cfg.h"

#include <pystring/pystring.h>

#include "glog/logging.h"

#include <algorithm>

Compare::Compare(const json& app_perf_result): app_perf_result_(app_perf_result) {
}


json Compare::get_api_products_fields(const std::map<std::string, std::string>& field_mapping) {
    auto start_date = app_perf_result_["start_date"];
    auto end_date = app_perf_result_["end_date"];
    auto countries = app_perf_result_["countries"];
    auto granularity = app_perf_result_["granularity"];
    auto devices = app_perf_result_["devices"];
    auto products = app_perf_result_["products"];
    auto api_fields = get_map_keys(field_mapping);

    json api_values {};
    for(auto&& product_: products) {
        json api_value {};
        auto product_id = product_["product_id"];
        auto market_code = product_["market_code"];
        json prod_{
            {"product_id", product_id},
            {"market_code", market_code},
            {"granularity", granularity},
            {"start_date", start_date},
            {"end_date", end_date},
            {"countries", countries},
            {"devices", devices}
        };
        api_value["product"] = prod_;
        json values {};
        json value {};
        for(auto api_field: api_fields) {
            value[api_field] = product_[api_field];
        }
        values.emplace_back(std::move(value));
        api_value["values"] = values;
        api_values.push_back(std::move(api_value));
    }
    return std::move(api_values);
}


json Compare::get_www_product_fields(const json& prod, const std::string& www_request_file_name, const std::map<std::string, std::string>& field_mapping) {
    auto dar_query_str = read_query_file_and_replace_consts(prod, www_request_file_name);
    LOG(ERROR) << dar_query_str << "\n";
    auto dar_query_res_str = Req::make_a_www_query(v2_query_path, dar_query_str);
    auto dar_query_res = json::parse(dar_query_res_str);
    auto field_values = get_map_values(field_mapping);
    auto www_query_tmp_res = parse_dim_product_fields(dar_query_res, field_values);
    auto www_query_res = convert_dim_values_to_api_values(www_query_tmp_res, field_mapping);

    return std::move(www_query_res);
}


bool Compare::compare_api_and_www_meta_equal(const std::map<std::string, std::string>& field_mappings, const std::string& www_query_file) {
    auto api_products_ = get_api_products_fields(field_mappings);
    bool is_value_equal = true;
    int i = 0;

    for(auto&& api_prod_: api_products_) {
        auto prod_ = api_prod_["product"];
        auto values_ = api_prod_["values"];
        ++i;
        // 对比前max_compare_count条，退出
        if(i > max_compare_count) {
                LOG(INFO) << "Hit " << max_compare_count << " records, return." << "\n";
                break;
        }
        
        auto www_values_ = get_www_product_fields(prod_, www_query_file, field_mappings);
        LOG(INFO) << values_.dump() << "\n";
        LOG(INFO) << www_values_.dump() << "\n";

        std::sort(values_.begin(), values_.end());
        std::sort(www_values_.begin(), www_values_.end());
        bool has_diff = find_diff_and_save_f(values_, www_values_, "www_meta_info");
        is_value_equal = !has_diff;
        if(!is_value_equal) {
            LOG(ERROR) << "API and www values are not equals\n";
            LOG(ERROR) << "API : www_meta_info\n"; 
            LOG(ERROR) << values_ << "\n";
            LOG(ERROR) << "WWW : www_meta_info\n";
            LOG(ERROR) << www_values_ << "\n";
            break;
        }
    }
    return is_value_equal;
}


json Compare::get_api_values(const std::map<std::string, std::string>& field_mappings, const std::string& data_field_name) {
    auto products_ = app_perf_result_["products"];
    auto start_date = app_perf_result_["start_date"];
    auto end_date = app_perf_result_["end_date"];
    auto countries = app_perf_result_["countries"];
    auto devices = app_perf_result_["devices"];
    auto granularity = app_perf_result_["granularity"];
    json api_values;
    for(auto&& product_ : products_) {
            json product_and_values;
            auto product_id = product_["product_id"];
            auto market_code = product_["market_code"];
            
            auto datas = product_[data_field_name];
            json prod_;
            prod_["product_id"] = product_id;
            prod_["market_code"] = market_code;
            prod_["granularity"] = granularity;
            prod_["start_date"] = start_date;
            prod_["end_date"] = end_date;
            prod_["countries"] = countries;
            prod_["devices"] = devices;

            product_and_values["product"] = prod_;

            json values;
            for(auto&& data : datas) {
                json value;
                for(auto&& key_map_item: field_mappings) {
                    auto api_key = key_map_item.first;
                    if(data[api_key].is_number_float() && (get_float_fraction(data[api_key].get<float>()) == 0.0)) {
                        value[api_key] = (uint64_t)(data[api_key].get<float>());
                    }else {
                        value[api_key] = data[api_key];
                    }
                }

                bool should_append = false;
                for(auto&& begin=value.begin(), end=value.end(); begin!=end; ++begin) {
                    auto key = begin.key();
                    auto key_it = std::find(common_keys.begin(), common_keys.end(), key);
                    // 没找着这个key
                    if(key_it == common_keys.end()) {
                        if(!value[key].is_null()) {
                        should_append = true;
                        break; 
                        }
                    }
                }
                if(should_append) {
                    values.emplace_back(std::move(value));
                }
            }
                    
            product_and_values["values"] = values;

            api_values.emplace_back(std::move(product_and_values));
    }
    return std::move(api_values);
}


json Compare::get_one_www_value(const json& prod, const std::string& www_request_file_name, const std::map<std::string, std::string>& field_mappings) {
        auto dar_query_str = read_query_file_and_replace_consts(prod, www_request_file_name);
        LOG(ERROR) << dar_query_str << "\n";
        auto dar_query_res_str = Req::make_a_www_query(v2_query_path, dar_query_str);
        auto dar_query_res = json::parse(dar_query_res_str);

        auto datas = dar_query_res["data"]["facets"];
        json product_and_values;

        product_and_values["product"] = prod;
        json values;
        for(auto&& data : datas) {
            json value;
            for(auto&& key_map_item: field_mappings) {
                auto api_key = key_map_item.first;
                auto www_key = key_map_item.second;
                if(www_key == "date") {
                    auto timestamp_ = data[www_key].get<uint64_t>();
                    auto date_str = timestamp_to_utc_time(timestamp_);
                    value[api_key] = date_str;
                }else{
                    // App Performance 接口Truncate了原先API接口返回的精度
                    if(data[www_key].is_number_float() && (get_float_fraction(data[www_key].get<float>()) == 0.0)) {
                        value[api_key] = (uint64_t)(data[www_key].get<float>());
                    }else {
                        value[api_key] = data[www_key];
                    }
                }
            }
            
            bool should_append = false;
            for(auto&& begin=value.begin(), end=value.end(); begin!=end; ++begin) {
                auto key = begin.key();
                auto key_it = std::find(common_keys.begin(), common_keys.end(), key);
                // 没找着这个key
                if(key_it == common_keys.end()) {
                    if(!value[key].is_null()) {
                       should_append = true;
                       break; 
                    }
                }
            }
            if(should_append) {
                values.emplace_back(std::move(value));
            }
        }

        product_and_values["values"] = values;
        return std::move(product_and_values);
}

bool Compare::compare_api_and_www_equal(const std::map<std::string, std::string>& field_mappings, const std::string& api_data_field_name, const std::string& result_file_name, const std::string& www_query_file) {

        auto api_values = get_api_values(field_mappings, api_data_field_name);
        bool is_value_equal = true;

        int i = 0;

        for(auto&& product_and_values: api_values) {
            auto product = product_and_values["product"];
            auto values_ = product_and_values["values"];

            auto www_values_ = get_one_www_value(
                product, www_query_file, field_mappings);
            auto act_www_values_ = www_values_["values"];

            ++i;
            // 对比前max_compare_count条，退出
            if(i > max_compare_count){
                LOG(INFO) << "Hit " << max_compare_count << " records, return\n.";
                break;
            }

            std::sort(values_.begin(), values_.end());
            std::sort(act_www_values_.begin(), act_www_values_.end());
            auto has_diff = find_diff_and_save_f(values_, act_www_values_, result_file_name);

            is_value_equal = !has_diff;
            if(!is_value_equal){
                LOG(ERROR) << "API and www values are not equals\n";
                LOG(ERROR) << "API Length: " << values_.size() << "\n";
                LOG(ERROR) << "WWW Length: " << act_www_values_.size() << "\n";
                
                LOG(ERROR) << "Product: \n";
                LOG(ERROR) << product << "\n";

                LOG(ERROR) << "API " << api_data_field_name << ": \n";
                LOG(ERROR) << values_ << "\n";
                LOG(ERROR) << "WWW " << api_data_field_name + ": \n";
                LOG(ERROR) << act_www_values_ << "\n";
                break;
            }
        }

        return is_value_equal;
}

bool Compare::compare_api_and_www_values_equal(const std::map<std::string, std::string>& field_mappings, const std::string& api_data_field_name, const std::vector<std::string>& www_query_file_list) {
        auto api_values = get_api_values(field_mappings, api_data_field_name);
        bool is_value_equal = true;

        int i = 0;

        for(auto&& product_and_values: api_values) {
            auto product = product_and_values["product"];
            auto values_ = product_and_values["values"];


            json act_www_values_;
            for(auto&& www_query_file : www_query_file_list) {
                auto www_values_ = get_one_www_value(
                    product, www_query_file, field_mappings);
                for(auto&& value:  www_values_["values"]) {
                    act_www_values_.emplace_back(std::move(value));
                }
            }

            ++i;

            // 比前max_compare_count条，退出
             // 对比前max_compare_count条，退出
            if(i > max_compare_count){
                LOG(INFO) << "Hit " << max_compare_count << " records, return\n.";
                break;
            }

            std::sort(values_.begin(), values_.end());
            std::sort(act_www_values_.begin(), act_www_values_.end());
            auto has_diff = find_diff_and_save_f(values_, act_www_values_, api_data_field_name);

            is_value_equal = !has_diff;
            if(!is_value_equal){
                LOG(ERROR) << "API and www values are not equals\n";
                LOG(ERROR) << "API Length: " << values_.size() << "\n";
                LOG(ERROR) << "WWW Length: " << act_www_values_.size() << "\n";
                
                LOG(ERROR) << "Product: \n";
                LOG(ERROR) << product << "\n";

                LOG(ERROR) << "API " << api_data_field_name << ": \n";
                LOG(ERROR) << values_ << "\n";
                LOG(ERROR) << "WWW " << api_data_field_name + ": \n";
                LOG(ERROR) << act_www_values_ << "\n";
                break;
            }
        }

        return is_value_equal;
}


json Compare::get_retention_www_values(const json& prod, const std::string& www_request_file_name, const RetentionValue& rent_value) {
        auto granu_ = rent_value.granularity;
        auto range_list = rent_value.range_list;

        auto dar_query_str = read_query_file_and_replace_consts(prod, www_request_file_name);
        dar_query_str =  pystring::replace(dar_query_str, "month", granu_);
        LOG(ERROR) << dar_query_str << "\n";

        auto dar_query_res_str = Req::make_a_www_query(v2_query_path, dar_query_str);
        auto dar_query_res = json::parse(dar_query_res_str);

        auto datas = dar_query_res["data"]["facets"];
        json product_and_values;
        product_and_values["product"] = prod;
        
        json tmp_list;
        json tmp_map;

        std::stringstream rent_key_ss {};
        rent_key_ss << "retention_" << granu_ << "s";
        auto rent_key = rent_key_ss.str();
        
        std::stringstream aggr_key_ss {};
        aggr_key_ss << "est_retention_" << granu_ << "__aggr";
        auto aggr_key = aggr_key_ss.str();

        std::string first_ch = granu_.substr(0, 1);
        std::stringstream rent_value_key_ss {};
        rent_value_key_ss << "est_retention_" << first_ch;
        auto rent_value_key = rent_value_key_ss.str();

        for(auto&& data: datas) {
            json value;
            auto timestamp_ = data["date"].get<uint64_t>();
            auto date_str = timestamp_to_utc_time(timestamp_);
            value["date"] = date_str;
            value["country_code"] = data["country_code"];
            value["device_code"] = data["device_code"];
            value[rent_key] = data[rent_key];
            value[aggr_key] = data[aggr_key];
            tmp_list.emplace_back(std::move(value));
        }
        for(auto&& dic_ele: tmp_list) {
            auto key_ = dic_ele["date"].get<std::string>() + "/" +dic_ele["device_code"].get<std::string>() + "/" + dic_ele["country_code"].get<std::string>();
            auto key_it = tmp_map.find(key_);
            if(key_it == tmp_map.end()) {
                tmp_map[key_] = {std::move(dic_ele)};
            } else {
                tmp_map[key_].emplace_back(std::move(dic_ele));
            }
        }
        
        for(auto&& begin=tmp_map.begin(), end=tmp_map.end(); begin!=end; ++begin) {
            auto date_ = begin.key();
            auto eles = begin.value();
            json res_value;
            std::vector<std::string> results_keys_{};
            pystring::split(date_, results_keys_, "/");
            res_value["date"] = results_keys_[0];
            res_value["device_code"] = results_keys_[1];
            res_value["country_code"] = results_keys_[2];
            std::vector<int> exist_months{};
            for(auto&& ele: eles) {
                auto rent_key_it = std::find(range_list.begin(), range_list.end(), ele[rent_key].get<int>());
                if(rent_key_it != range_list.end()) {
                    std::stringstream res_key_ss{};
                    res_key_ss << rent_value_key << ele[rent_key].get<int>();
                    auto res_key = res_key_ss.str();
                    
                    if(ele[aggr_key].is_number_float() && (get_float_fraction(ele[aggr_key].get<float>()) == 0.0)) {
                        res_value[res_key] = (uint64_t)(ele[aggr_key].get<float>());
                    }else {
                        res_value[res_key] = ele[aggr_key];
                    }

                    exist_months.emplace_back(ele[rent_key].get<int>());
                }    
            }

            std::sort(range_list.begin(), range_list.end());
            std::sort(exist_months.begin(), exist_months.end());
        
            std::vector<int> not_exist_months {}; 
        
            std::set_difference(range_list.begin(), range_list.end(),
                exist_months.begin(), exist_months.end(),
                std::back_inserter(not_exist_months));
          
            for(auto&& not_exist_month: not_exist_months) {
                std::stringstream res_key_ss1{};
                res_key_ss1 << rent_value_key << not_exist_month;
                auto res_key = res_key_ss1.str();
                res_value[res_key] = nullptr;
            }
                
            product_and_values["values"].emplace_back(std::move(res_value));
        }
        return std::move(product_and_values);
}

bool Compare::compare_api_and_www_retention_equal(const std::map<std::string, RetentionValue>& field_mappings, const std::string& api_data_field_name, const std::string& result_file_name,  const std::string& www_query_file) {
        auto granularity = app_perf_result_["granularity"].get<std::string>();
        auto rent_value = field_mappings.find(granularity)->second;

        auto real_mappings_ = rent_value.mapping;
        auto api_values = get_api_values(real_mappings_, api_data_field_name);

        bool is_value_equal = true;

        int i = 0;


        for(auto&& product_and_values: api_values) {
            auto product = product_and_values["product"];
            auto values_ = product_and_values["values"];

            auto www_values_ = get_retention_www_values(
                product, www_query_file, rent_value);
            auto act_www_values_ = www_values_["values"];

            ++i;
            // 对比前max_compare_count条，退出
            if(i > max_compare_count){
                LOG(INFO) << "Hit " << max_compare_count << " records, return\n.";
                break;
            }

            std::sort(values_.begin(), values_.end());
            std::sort(act_www_values_.begin(), act_www_values_.end());
            auto has_diff = find_diff_and_save_f(values_, act_www_values_, result_file_name);

            is_value_equal = !has_diff;
            if(!is_value_equal){
                LOG(ERROR) << "API and www values are not equals\n";
                LOG(ERROR) << "API Length: " << values_.size() << "\n";
                LOG(ERROR) << "WWW Length: " << act_www_values_.size() << "\n";
                
                LOG(ERROR) << "Product: \n";
                LOG(ERROR) << product << "\n";

                LOG(ERROR) << "API " << api_data_field_name << ": \n";
                LOG(ERROR) << values_ << "\n";
                LOG(ERROR) << "WWW " << api_data_field_name + ": \n";
                LOG(ERROR) << act_www_values_ << "\n";
                break;
            }
        }
        return is_value_equal;
}