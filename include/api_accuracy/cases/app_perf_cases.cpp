#include "api_accuracy/cases/app_perf_cases.h"

std::vector<Case> app_perf_pos_cases {
    {"../datas/app_perf/test545__200_ok_monthly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=monthly&start_date=2020-01-01&end_date=2020-03-31&countries=US,CN,JP,GB", 0},
    {"../datas/app_perf/test546__200_ok_daily_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=daily&start_date=2020-01-01&end_date=2020-01-10&countries=US,CN", 0},
    {"../datas/app_perf/test547__200_ok_weekly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=weekly&start_date=2020-01-01&end_date=2020-01-31&countries=US,CN", 0},
    {"../datas/app_perf/test548__200_ok_by_apps_api_response", "/v1.3/portfolio/app-performance/less?apps=284882215,20600000009072,30600000702686&granularity=monthly&start_date=2020-01-01&end_date=2020-03-31&countries=US", 0},
    {"../datas/app_perf/test549__200_ok_all_countries_api_response", "/v1.3/portfolio/app-performance/less?apps=284882215&granularity=monthly&start_date=2020-01-01&end_date=2020-01-31", 0},
    {"../datas/app_perf/test550__200_ok_filter_device_api_response", "/v1.3/portfolio/app-performance/less?apps=284882215,20600000009072&granularity=monthly&start_date=2020-01-01&end_date=2020-01-31&countries=US&device=ios-phone", 0},
    {"../datas/app_perf/test556__200_ok_missing_granularity_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&start_date=2020-01-01&end_date=2020-01-01&countries=US", 0},
    {"../datas/app_perf/test561__200_param_all_metric_api_response", "/v1.3/portfolio/app-performance/less?apps=284882215&granularity=daily&start_date=2020-01-01&end_date=2021-01-01&countries=US&metric=all", 0},
    {"../datas/app_perf/test562__200_param_all_device_api_response", "/v1.3/portfolio/app-performance/less?apps=284882215,20600000009072&granularity=daily&start_date=2020-01-01&end_date=2021-01-01&countries=US&device=all", 0}
};

std::vector<Case> app_perf_neg_cases {
    {"test551__400_err_invalid_country", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=monthly&start_date=2020-01-01&end_date=2020-01-31&countries=YY", 400},
    {"test552__400_err_invalid_device_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=monthly&start_date=2020-01-01&end_date=2020-01-31&device=vivo-phone", 400},
    {"test553__400_err_invalid_granularity", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=anually&start_date=2020-01-01&end_date=2020-01-31", 400},
    {"test554__400_err_invalid_entry", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&apps=284882215&granularity=monthly&start_date=2020-01-01&end_date=2020-01-31", 400},
    {"test555__400_err_missing_entry", "/v1.3/portfolio/app-performance/less?granularity=monthly&start_date=2020-01-01&end_date=2020-01-31", 400},
    {"test557__400_err_missing_start_date", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=daily&end_date=2020-01-31", 400},
    {"test558__400_err_missing_end_date", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=daily&start_date=2020-01-01", 400},
    {"test559__400_invalid_company_id", "/v1.3/portfolio/app-performance/less?company_id=facebook&granularity=daily&start_date=2020-01-01&end_date=2021-01-01", 400},
    {"test559__400_invalid_product_id", "/v1.3/portfolio/app-performance/less?apps=instagram&granularity=daily&start_date=2020-01-01&end_date=2021-01-01", 400},
    {"test563__400_invalid_metric", "/v1.3/portfolio/app-performance/less?apps=284882215&granularity=daily&start_date=2020-01-01&end_date=2021-01-01&metric=usage,non_existed", 400}
};

std::vector<Case> app_perf_perf_cases {
    {"test545__200_ok_daily_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=daily&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB", 0},
    {"test546__200_ok_weekly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=weekly&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB", 0},
    {"test547__200_ok_monthly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=monthly&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB", 0},


    {"test545__200_ok_daily_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000324528&granularity=daily&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB", 0},
    {"test546__200_ok_weekly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000324528&granularity=weekly&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB", 0},
    {"test547__200_ok_monthly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000324528&granularity=monthly&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB", 0},


    {"test545__200_ok_daily_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000095224&granularity=daily&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB", 0},
    {"test546__200_ok_weekly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000095224&granularity=weekly&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB", 0},
    {"test547__200_ok_monthly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000095224&granularity=monthly&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB", 0},


    {"test545__200_ok_daily_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000049444&granularity=daily&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB", 0},
    {"test546__200_ok_weekly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000049444&granularity=weekly&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB", 0},
    {"test547__200_ok_monthly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000049444&granularity=monthly&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB", 0},

    // All supported countries 

    {"test545__200_ok_daily_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=daily&start_date=2020-01-01&end_date=2020-01-01", 0},
    {"test546__200_ok_weekly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=weekly&start_date=2020-01-01&end_date=2020-01-01", 0},
    {"test547__200_ok_monthly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=monthly&start_date=2020-01-01&end_date=2020-01-01", 0},


    {"test545__200_ok_daily_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000324528&granularity=daily&start_date=2020-01-01&end_date=2020-01-01", 0},
    {"test546__200_ok_weekly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000324528&granularity=weekly&start_date=2020-01-01&end_date=2020-01-01", 0},
    {"test547__200_ok_monthly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000324528&granularity=monthly&start_date=2020-01-01&end_date=2020-01-01", 0},


    {"test545__200_ok_daily_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000095224&granularity=daily&start_date=2020-01-01&end_date=2020-01-01", 0},
    {"test546__200_ok_weekly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000095224&granularity=weekly&start_date=2020-01-01&end_date=2020-01-01", 0},
    {"test547__200_ok_monthly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000095224&granularity=monthly&start_date=2020-01-01&end_date=2020-01-01", 0},


    {"test545__200_ok_daily_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000049444&granularity=daily&start_date=2020-01-01&end_date=2020-01-01", 0},
    {"test546__200_ok_weekly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000049444&granularity=weekly&start_date=2020-01-01&end_date=2020-01-01", 0},
    {"test547__200_ok_monthly_api_response", "/v1.3/portfolio/app-performance/less?company_id=1000200000049444&granularity=monthly&start_date=2020-01-01&end_date=2020-01-01", 0},

};


std::vector<AsyncCase> app_perf_async_cases {
    // monthly cases
    {"test545__200_ok_monthly_api_sync_async_equal",
             "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=monthly&start_date=2020-01-01&end_date=2020-03-31&countries=US,CN,JP,GB",
             0,
             "/v1.3/portfolio/app-performance?company_id=1000200000000034&granularity=monthly&start_date=2020-01-01&end_date=2020-03-31&countries=US,CN,JP,GB",
             0},

    {"test545__200_ok_monthly_api_sync_async_greater",
             "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=monthly&start_date=2020-01-01&end_date=2020-03-31&countries=US,CN,JP,GB",
             0,
             "/v1.3/portfolio/app-performance?company_id=1000200000000034&granularity=monthly&start_date=2020-01-01&end_date=2020-04-30&countries=US,CN,JP,GB",
             0},


    // daily cases
    {"test546__200_ok_daily_api_sync_async_equal", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=daily&start_date=2020-01-01&end_date=2020-01-10&countries=US,CN", 0, "/v1.3/portfolio/app-performance?company_id=1000200000000034&granularity=daily&start_date=2020-01-01&end_date=2020-01-10&countries=US,CN", 0},

    {"test546__200_ok_daily_api_sync_async_greater", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=daily&start_date=2020-01-01&end_date=2020-01-10&countries=US,CN", 0, "/v1.3/portfolio/app-performance?company_id=1000200000000034&granularity=daily&start_date=2020-01-01&end_date=2020-01-13&countries=US,CN", 0},

    // ## weekly cases
    {"test547__200_ok_weekly_api_sync_async_equal", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=weekly&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB", 0, "/v1.3/portfolio/app-performance?company_id=1000200000000034&granularity=weekly&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB", 0},

    {"test547__200_ok_weekly_api_sync_async_greater", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&granularity=weekly&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB", 0, "/v1.3/portfolio/app-performance?company_id=1000200000000034&granularity=weekly&start_date=2020-01-01&end_date=2020-01-20&countries=US,CN,JP,GB", 0},


    // ## By apps cases
    {"test548__200_ok_by_apps_api_sync_async_equal", "/v1.3/portfolio/app-performance/less?product_id=284882215,20600000009072,30600000702686&granularity=monthly&start_date=2020-01-01&end_date=2020-03-31&countries=US", 0, "/v1.3/portfolio/app-performance?product_id=284882215,20600000009072,30600000702686&granularity=monthly&start_date=2020-01-01&end_date=2020-03-31&countries=US", 0},

    {"test548__200_ok_by_apps_api_sync_async_greater", "/v1.3/portfolio/app-performance/less?product_id=284882215,20600000009072,30600000702686&granularity=monthly&start_date=2020-01-01&end_date=2020-02-28&countries=US", 0, "/v1.3/portfolio/app-performance?product_id=284882215,20600000009072,30600000702686&granularity=monthly&start_date=2020-01-01&end_date=2020-03-31&countries=US", 0},


    // ## All countries cases
    {"test549__200_ok_all_countries_api_sync_async_equal", "/v1.3/portfolio/app-performance/less?product_id=284882215&granularity=monthly&start_date=2020-01-01&end_date=2020-01-31", 0, "/v1.3/portfolio/app-performance?product_id=284882215&granularity=monthly&start_date=2020-01-01&end_date=2020-01-31", 0},

    {"test549__200_ok_all_countries_api_sync_async_greater", "/v1.3/portfolio/app-performance/less?product_id=284882215&granularity=monthly&start_date=2020-01-01&end_date=2020-01-31", 0, "/v1.3/portfolio/app-performance?product_id=284882215&granularity=monthly&start_date=2020-01-01&end_date=2020-02-28", 0},
    

    // ## Filter by device cases
    {"test550__200_ok_filter_device_api_sync_async_equal", "/v1.3/portfolio/app-performance/less?product_id=284882215,20600000009072&granularity=monthly&start_date=2020-01-01&end_date=2020-01-31&countries=US&device=ios-phone", 0, "/v1.3/portfolio/app-performance?product_id=284882215,20600000009072&granularity=monthly&start_date=2020-01-01&end_date=2020-01-31&countries=US&device=ios-phone", 0},

    {"test550__200_ok_filter_device_api_sync_async_greater", "/v1.3/portfolio/app-performance/less?product_id=284882215,20600000009072&granularity=monthly&start_date=2020-01-01&end_date=2020-01-31&countries=US&device=ios-phone", 0, "/v1.3/portfolio/app-performance?product_id=284882215,20600000009072&granularity=monthly&start_date=2020-01-01&end_date=2020-02-28&countries=US&device=ios-phone", 0},
    

    // ## missing granularity cases
    {"test556__200_ok_missing_granularity_api_sync_async_equal", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&start_date=2020-01-01&end_date=2020-01-01&countries=US", 0,
    "/v1.3/portfolio/app-performance?company_id=1000200000000034&start_date=2020-01-01&end_date=2020-01-01&countries=US", 0},
    {"test556__200_ok_missing_granularity_api_sync_async_greater", "/v1.3/portfolio/app-performance/less?company_id=1000200000000034&start_date=2020-01-01&end_date=2020-01-01&countries=US", 0,
    "/v1.3/portfolio/app-performance?company_id=1000200000000034&start_date=2020-01-01&end_date=2020-01-03&countries=US", 0},


    // ## all metric cases No need to do
    {"test561__200_param_all_metric_api_sync_async_equal", "/v1.3/portfolio/app-performance/less?product_id=284882215&granularity=daily&start_date=2020-01-01&end_date=2020-05-01&countries=US&metric=all", 0,
    "/v1.3/portfolio/app-performance?product_id=284882215&granularity=daily&start_date=2020-01-01&end_date=2020-05-01&countries=US&metric=all",
    0},
    {"test561__200_param_all_metric_api_sync_async_greater", "/v1.3/portfolio/app-performance/less?product_id=284882215&granularity=daily&start_date=2020-01-01&end_date=2020-05-01&countries=US&metric=all", 0,
    "/v1.3/portfolio/app-performance?product_id=284882215&granularity=daily&start_date=2020-01-01&end_date=2020-07-01&countries=US&metric=all",
    0},

    // # All device cases
    {"test562__200_param_all_device_api_sync_async_equal", "/v1.3/portfolio/app-performance/less?product_id=284882215,20600000009072&granularity=daily&start_date=2020-01-01&end_date=2020-05-01&countries=US&device=all", 0, "/v1.3/portfolio/app-performance?product_id=284882215,20600000009072&granularity=daily&start_date=2020-01-01&end_date=2020-05-01&countries=US&device=all", 0},
    
    {"test562__200_param_all_device_api_sync_async_greater", "/v1.3/portfolio/app-performance/less?product_id=284882215,20600000009072&granularity=daily&start_date=2020-01-01&end_date=2020-05-01&countries=US&device=all", 0, "/v1.3/portfolio/app-performance?product_id=284882215,20600000009072&granularity=daily&start_date=2020-01-01&end_date=2020-07-01&countries=US&device=all", 0},
};


std::vector<Case> app_perf_async_perf_cases {
    {"test545__200_ok_monthly_api_async_case", "/v1.3/portfolio/app-performance?product_id=284882215&granularity=daily&start_date=2020-01-01&end_date=2020-01-03&countries=US", 0}
};


std::vector<Case> app_perf_async_concurr_perf_cases {
    // FaceBook cases for specific countries
    {"test545__200_ok_facebook_daily_api_basic_concurr_case", "/v1.3/portfolio/app-performance?company_id=1000200000000034&granularity=daily&start_date=2020-01-01&end_date=2020-01-01&countries=US,CN,JP,GB", 0},
    
    {"test546__200_ok_facebook_daily_api_max_concurr_case", "/v1.3/portfolio/app-performance?company_id=1000200000000034&granularity=daily&start_date=2017-01-01&end_date=2017-07-10&countries=US,CN,JP,GB", 0},

    {"test547__200_ok_facebook_weekly_api_max_concurr_case", "/v1.3/portfolio/app-performance?company_id=1000200000000034&granularity=weekly&start_date=2017-01-01&end_date=2019-12-22&countries=US,CN,JP,GB", 0},

    {"test548__200_ok_facebook_monthly_api_max_concurr_case", "/v1.3/portfolio/app-performance?company_id=1000200000000034&granularity=monthly&start_date=2017-01-01&end_date=2021-03-01&countries=US,CN,JP,GB", 0},

    // Pearl Gmbh cases for specific countries
    {"test549__200_ok_pearl_gmbh_daily_api_max_concurr_case", "/v1.3/portfolio/app-performance?company_id=1000200000324528&granularity=daily&start_date=2017-01-01&end_date=2017-01-21&countries=US,CN,JP,GB", 0},
   
    {"test550__200_ok_pearl_gmbh_weekly_api_max_concurr_case", "/v1.3/portfolio/app-performance?company_id=1000200000324528&granularity=weekly&start_date=2017-01-01&end_date=2019-06-30&countries=US,CN,JP,GB", 0},

    {"test551__200_ok_pearl_gmbh_monthly_api_max_concurr_case", "/v1.3/portfolio/app-performance?company_id=1000200000324528&granularity=monthly&start_date=2017-01-01&end_date=2018-09-01&countries=US,CN,JP,GB", 0},

    // Shiyuan cases for specific countries
    {"test552__200_ok_pearl_shiyuan_daily_api_max_concurr_case", "/v1.3/portfolio/app-performance?company_id=1000200000095224&granularity=daily&start_date=2017-01-01&end_date=2019-04-01&countries=US,CN,JP,GB", 0},

    {"test553__200_ok_pearl_shiyuan_weekly_api_max_concurr_case", "/v1.3/portfolio/app-performance?company_id=1000200000095224&granularity=weekly&start_date=2017-01-01&end_date=2021-09-12&countries=US,CN,JP,GB", 0},

    {"test554__200_ok_pearl_shiyuan_monthly_api_max_concurr_case", "/v1.3/portfolio/app-performance?company_id=1000200000095224&granularity=monthly&start_date=2017-01-01&end_date=2018-09-01&countries=US,CN,JP,GB", 0},

    // ENURI cases for specific countries
    {"test555__200_ok_enuri_daily_api_max_concurr_case", "/v1.3/portfolio/app-performance?company_id=1000200000049444&granularity=daily&start_date=2017-01-01&end_date=2018-08-09&countries=US,CN,JP,GB", 0},

    {"test556__200_ok_enuri_weekly_api_max_concurr_case", "/v1.3/portfolio/app-performance?company_id=1000200000049444&granularity=weekly&start_date=2017-01-01&end_date=2021-09-12&countries=US,CN,JP,GB", 0},

    {"test557__200_ok_enuri_monthly_api_max_concurr_case", "/v1.3/portfolio/app-performance?company_id=1000200000049444&granularity=monthly&start_date=2017-01-01&end_date=2021-03-01&countries=US,CN,JP,GB", 0},

    // ENURI cases for all countries
    {"test558__200_ok_enuri_daily_api_max_all_countries_concurr_case", "/v1.3/portfolio/app-performance?company_id=1000200000049444&granularity=daily&start_date=2017-01-01&end_date=2019-04-11", 0},

    {"test559__200_ok_enuri_weekly_api_max_all_countries_concurr_case", "/v1.3/portfolio/app-performance?company_id=1000200000049444&granularity=weekly&start_date=2017-01-01&end_date=2021-09-12", 0},

    {"test559__200_ok_enuri_monthly_api_max_all_countries_concurr_case", "/v1.3/portfolio/app-performance?company_id=1000200000049444&granularity=monthly&start_date=2017-01-01&end_date=2021-03-01", 0},
};