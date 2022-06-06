#include "locale2_/locale2_.h"
#include "json/json.hpp"
#include "locale2_/languages.h"
#include "sf_db2/sf_db2.h"
#include "pystring/pystring.h"
#include "locale2_/currency.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

using json = nlohmann::json;


const std::string ConnStr = "dsn=product_odbc;pwd=Lily870104";
const int IosCountrySize = 63;
const int GPCountrySize = 64;

std::string get_country_by_locale(const std::string& locale) {
    auto start_it = locale.find("-", 0);
    std::string country_val{};
    if (start_it != std::string::npos) {
        country_val = locale.substr(start_it + 1, locale.size() - start_it - 1);
    }
    return std::move(country_val);
}

std::set<std::string> convert_locales_to_countries(
    const std::set<std::string>& locales) {
    std::set<std::string> res{};
    for (auto&& locale : locales) {
        auto country = get_country_by_locale(locale);
        res.insert(country);
    }
    return std::move(res);
}

bool compare_locales_and_country_code(const std::set<std::string>& locales_,
                                      const std::string& country_file_path,  
                                      const int country_size) {
    std::ifstream ifs{country_file_path};
    std::stringstream ss;
    ss << ifs.rdbuf();
    auto country_list = json::parse(ss.str());
    std::set<std::string> country_values{};
    for (auto&& country_sub_list : country_list) {
        if (nullptr != country_sub_list) {
            auto options = country_sub_list["options"];
            for (auto&& country : options) {
                if(nullptr != country["value"]) {
                    auto country_value = country["value"].get<std::string>();
                    country_values.insert(country_value);
                }
            }
        }
    }
    auto countries_ = convert_locales_to_countries(locales_);
    std::vector<std::string> res{};
    std::set_intersection(country_values.begin(), country_values.end(),
                          countries_.begin(), countries_.end(),
                          std::back_inserter(res));

    std::vector<std::string> diff{};

    std::set_difference(countries_.begin(), countries_.end(), res.begin(),
                        res.end(), std::back_inserter(diff));
    std::cout << "Diff Element: " << std::endl;
    for (auto&& ele : diff) {
        std::cout << ele << std::endl;
    }
    return res.size() == country_size;
}

bool compare_locales_and_country_code_ios() {
    return compare_locales_and_country_code(ios_locales, ios_country_file_path, IosCountrySize);
}

bool compare_locales_and_country_code_ios_timeline() {
    return compare_locales_and_country_code(ios_locales, ios_timeline_country_file_path, IosCountrySize);
}

bool compare_locales_and_country_code_gp() {
    return compare_locales_and_country_code(gp_locales, gp_country_file_path, GPCountrySize);
}

bool compare_locales_and_country_code_gp_timeline() {
     return compare_locales_and_country_code(ios_locales, gp_timeline_country_file_path, IosCountrySize);
}


std::map<std::string, std::string> read_js_to_map(const std::string& js_file_name) {
    std::map<std::string, std::string> ret_map {};
    std::ifstream ifs {js_file_name};
    std::string line;
    while(std::getline(ifs, line)) {
        if(line.find(":")!=std::string::npos) {
            std::vector<std::string> res;
            pystring::split(line, res, ":");
            auto key = pystring::strip(res[0]);
            auto val_with_comma = pystring::strip(res[1]);
            auto val = val_with_comma.substr(1, val_with_comma.size()-3);
            ret_map[key] = val;
        }
    }
    ifs.close();
    return ret_map;
 }

bool check_locales_and_currencies() {
    auto currency_sign_map = read_js_to_map(currency_sign_file_path);
    auto currency_name_map = read_js_to_map(currency_name_file_path);
    sf_connection conn {ConnStr};
    
    std::vector<currency> currencies {};

    for(auto&& locale_: ios_locales) {
        auto country = get_country_by_locale(locale_);
        auto curr_name = currency_name_map[country];
        auto curr_sign = currency_sign_map[curr_name];

        std::stringstream ss;
        ss <<  R"(select top_in_app_list
    from AA_INTELLIGENCE_PRODUCTION.ADL_MASTER.DIM_PRODUCT_LOCALIZED_DETAIL_V1_CLUSTER_BY_PRODUCT_KEY
    where locale=')";
        ss << locale_;
        ss << R"(' and market_code='apple-store'
    and top_in_app_list is not null limit 1;)";
        auto raw_query = ss.str();

        auto res = conn.exec_raw_query(raw_query);

        std::string final_db_sign {};
        const std::string null_value = "null";
        if(res.next()) {
            auto db_sign_str = res.get<std::string>(0, null_value);
            auto db_sign_obj = json::parse(db_sign_str);
            final_db_sign = db_sign_obj[0]["raw_price_string"].get<std::string>();
        }

        auto curr = currency{country, curr_name, curr_sign, locale_, final_db_sign};
        currencies.emplace_back(std::move(curr));
    }

    int not_equal_count {0};
    std::cerr << "DB and UI sign not equal: " << std::endl;

    for(auto&& curr_: currencies) {
        if(curr_.db_sign.find(curr_.currency_sign) == std::string::npos) {        
            std::cerr << "Locale: [" << curr_.locale << "] "
            << "UI currency: [" << curr_.currency_sign << "] "
            << "DB currency: [" << curr_.db_sign << "]" << std::endl;
            ++not_equal_count;
        }
    }

    std::cout << "Not equal count: " << not_equal_count << std::endl;
    return (not_equal_count == 0);
}

std::set<std::string> get_available_country_names(const std::string& option_file_path, 
    const std::set<std::string> locales_) {
    std::set<std::string> ret{};
    
    std::ifstream ifs{option_file_path};
    std::stringstream ss;
    ss << ifs.rdbuf();
    auto country_list = json::parse(ss.str());

    for(auto&& locale_: locales_) {
        auto country_code = locale_.substr(3);
        for(auto&& country_: country_list) {
            if(!country_.is_null()) {
                auto options = country_["options"];
                for(auto&& option_: options) {

                    if(!option_["value"].is_null()) {
                        auto value = option_["value"].get<std::string>();
                        if(country_code == value) {
                            auto label = option_["label"].get<std::string>();
                            ret.insert(label);
                        }
                    }
                }
            }
        }
    }
    return std::move(ret);
}


std::set<std::string> get_available_ios_countries() {
    auto ret = get_available_country_names(ios_country_file_path, ios_locales);
    return ret;
}

std::set<std::string> get_available_gp_countries(){
    auto ret = get_available_country_names(gp_country_file_path, gp_locales);
    return ret;
}