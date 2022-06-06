#include "locale_/locale_.h"
#include "sf_db2/sf_db2.h"
#include <cassert>
#include <algorithm>
#include "glog/logging.h"

const std::string ConnStr = "dsn=product_odbc;pwd=Lily870104";
const int IosCountrySize = 63;
const int GPCountrySize = 64;
bool get_and_compare_countrires(const std::vector<std::string>& source_locales, const std::string& get_sql,
    int country_size) {
    
    auto conn_str = ConnStr;
    sf_connection sf{conn_str};
    auto res = sf.exec_raw_query(get_sql);
    std::vector<std::string> dest_locales {};

    const std::string null_value = "null";
    while (res.next()) {
        auto value = res.get<std::string>(0, null_value);
        dest_locales.emplace_back(std::move(value));
    }
    
    std::vector<std::string> failed_locales {};
    for(auto&& locale: source_locales) {
        auto res = std::find(dest_locales.begin(), dest_locales.end(), locale);
        if(res == dest_locales.end()) {
            std::cout << locale << " verify failed!" << std::endl;
            failed_locales.emplace_back(std::move(locale));
        }
    }

    if(failed_locales.size() != 0) {
        LOG(ERROR) << "Locales are not equal " << "\n";
        LOG(ERROR) << "Db rows: " << res.affected_rows() << "\n";
        LOG(ERROR) << "Country size: " << country_size << "\n";
        LOG(ERROR) << "Failed locales: \n";
        std::for_each(failed_locales.begin(), failed_locales.end(), [](const auto& ele_){
            LOG(ERROR) << ele_ << " ";
        });
        LOG(ERROR) << "\n";
    }
    return failed_locales.size()==0;
}

bool get_and_compare_ios_countries(const std::vector<std::string>& source_locales) {
    auto raw_query =
    R"(select distinct concat(language_code,'-', country_code) as locale, market_code 
    from AA_INTELLIGENCE_PRODUCTION.ADL_MASTER.DIM_PRODUCT_LOCALIZED_DETAIL_V1_CLUSTER_BY_PRODUCT_KEY
    where market_code='apple-store' and scraped_time='2021-12-05')";
    auto res = get_and_compare_countrires(source_locales, raw_query, IosCountrySize);
    return res;
}

bool get_and_compare_ios_countries_timeline(const std::vector<std::string>& source_locales) {
    auto raw_query =
    R"(select distinct locale, market_code 
    from AA_INTELLIGENCE_PRODUCTION.ADL_MASTER.dim_localized_event_service_v1_cluster_by_product_key
    where market_code='apple-store';)";
    auto res = get_and_compare_countrires(source_locales, raw_query, IosCountrySize);
    return res;
}

bool get_and_compare_gp_countries(const std::vector<std::string>& source_locales) {
    auto conn_str = ConnStr;
    auto raw_query =
    R"(select distinct concat(language_code,'-', country_code) as locale,market_code 
        from AA_INTELLIGENCE_PRODUCTION.ADL_MASTER.DIM_PRODUCT_LOCALIZED_DETAIL_V1_CLUSTER_BY_PRODUCT_KEY
        where market_code='google-play' and scraped_time='2021-12-05')";
    
    auto res = get_and_compare_countrires(source_locales, raw_query, GPCountrySize);
    return res;
}


bool get_and_compare_gp_countries_timeline(const std::vector<std::string>& source_locales) {
    auto raw_query =
    R"(select distinct locale, market_code 
    from AA_INTELLIGENCE_PRODUCTION.ADL_MASTER.dim_localized_event_service_v1_cluster_by_product_key
    where market_code='google-play';)";
    auto res = get_and_compare_countrires(source_locales, raw_query, GPCountrySize);
    return res;
}