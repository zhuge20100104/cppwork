#include "api_accuracy/utils/beans.h"

std::vector<int> day_ls {0, 1, 2, 3, 4, 5, 6, 7, 14, 30};
std::vector<int> week_ls {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20};
std::vector<int> month_ls {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

std::map<std::string, std::string> DimProductMapping {
    {"product_id", "product_id"},
    {"product_name", "name"},
    {"product_description", "description"},
    {"category_id", "category_id"},
    {"unified_product_id", "unified_product_id"},
    {"category_name", "category_id/name"},
    {"category_slug", "category_id/slug"},
    {"market_code", "market_code"},
    {"publisher_name", "publisher_id/name"},
    {"publisher_market", "publisher_id/market_code"},
    {"company_name", "publisher_id/company_id/name"},
    {"company_exchange", "publisher_id/company_id/exchange"},
    {"company_stock_symbol", "publisher_id/company_id/ticker_symbol"},
    {"company_website", "publisher_id/company_id/website"},
    {"company_is_public", "publisher_id/company_id/is_public_company"}
};

std::map<std::string, std::string> DownloadAndRevenueMapping {
    {"date", "date"},
    {"country_code", "country_code"},
    {"device_code", "device_code"},
    {"est_download", "est_download__sum"},
    {"est_revenue", "est_revenue__sum"},
    {"est_paid_channel_download", "est_paid_channel_download__sum"},
    {"est_organic_channel_download", "est_organic_channel_download__sum"},
    {"est_paid_channel_download_share", "est_paid_channel_download_share__aggr"},
    {"est_organic_channel_download_share", "est_organic_channel_download_share__aggr"}
};

std::map<std::string, std::string> UsageMapping {
    {"date", "date"},
    {"country_code", "country_code"},
    {"device_code", "device_code"},
    {"est_average_active_users", "est_average_active_users__aggr"},
    {"est_usage_penetration", "est_usage_penetration__aggr"},
    {"est_install_penetration", "est_install_penetration__aggr"},
    {"est_install_base", "est_install_base__aggr"},
    {"est_open_rate", "est_open_rate__aggr"},
    {"est_average_session_per_user", "est_average_session_per_user__aggr"},
    {"est_average_session_duration", "est_average_session_duration__aggr"},
    {"est_average_time_per_user", "est_average_time_per_user__aggr"},
    {"est_total_time", "est_total_time__aggr"},
    {"est_average_active_days", "est_average_active_days__aggr"},
    {"est_percentage_active_days", "est_percentage_active_days__aggr"},
    {"est_share_of_category_time", "est_share_of_category_time__aggr"},
    {"est_average_bytes_per_user", "est_average_bytes_per_user__aggr"},
    {"est_average_bytes_per_session", "est_average_bytes_per_session__aggr"}
};

std::map<std::string, std::string> DemographicsMapping = {
    {"date", "date"},
    {"country_code", "country_code"},
    {"est_demographics_percent", "est_demographics_percent__aggr"},
    {"est_demographics_index", "est_demographics_index__aggr"}
};

std::map<std::string, std::string> RetentionDayMapping = {
    {"date", "date"},
    {"country_code", "country_code"},
    {"device_code", "device_code"},
    {"est_retention_d0", "est_retention_d0"},
    {"est_retention_d1", "est_retention_d1"},
    {"est_retention_d2", "est_retention_d2"},
    {"est_retention_d3", "est_retention_d3"},
    {"est_retention_d4", "est_retention_d4"},
    {"est_retention_d5", "est_retention_d5"},
    {"est_retention_d6", "est_retention_d6"},
    {"est_retention_d7", "est_retention_d7"},
    {"est_retention_d14", "est_retention_d14"},
    {"est_retention_d30", "est_retention_d30"}
};

std::map<std::string, std::string> RetentionWeekMapping = {
    {"date", "date"},
    {"country_code", "country_code"},
    {"device_code", "device_code"},
    {"est_retention_w0", "est_retention_w0"},
    {"est_retention_w1", "est_retention_w1"},
    {"est_retention_w2", "est_retention_w2"},
    {"est_retention_w3", "est_retention_w3"},
    {"est_retention_w4", "est_retention_w4"},
    {"est_retention_w5", "est_retention_w5"},
    {"est_retention_w6", "est_retention_w6"},
    {"est_retention_w7", "est_retention_w7"},
    {"est_retention_w8", "est_retention_w8"},
    {"est_retention_w9", "est_retention_w9"},
    {"est_retention_w10", "est_retention_w10"},
    {"est_retention_w20", "est_retention_w20"}
};

std::map<std::string, std::string> RetentionMonthMapping = {
    {"date", "date"},
    {"country_code", "country_code"},
    {"device_code", "device_code"},
    {"est_retention_m0", "est_retention_m0"},
    {"est_retention_m1", "est_retention_m1"},
    {"est_retention_m2", "est_retention_m2"},
    {"est_retention_m3", "est_retention_m3"},
    {"est_retention_m4", "est_retention_m4"},
    {"est_retention_m5", "est_retention_m5"},
    {"est_retention_m6", "est_retention_m6"},
    {"est_retention_m7", "est_retention_m7"},
    {"est_retention_m8", "est_retention_m8"},
    {"est_retention_m9", "est_retention_m9"},
    {"est_retention_m10", "est_retention_m10"},
    {"est_retention_m11", "est_retention_m11"},
    {"est_retention_m12", "est_retention_m12"}
};


std::map<std::string, RetentionValue> RetetionMappingObject = {
    {"daily", {"day", RetentionDayMapping, day_ls}},
    {"weekly",{"week", RetentionWeekMapping, week_ls}},
    {"monthly", {"month", RetentionMonthMapping, month_ls}}
};