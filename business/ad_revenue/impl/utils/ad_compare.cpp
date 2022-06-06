#include "utils/ad_compare.h"
#include "utils/ad_revenue_cfg.h"
#include "glog/logging.h"

#include "json/json.hpp"
#include <sstream>
#include <iomanip>

using json = nlohmann::json;

double get_zero_or_value(json const& ele) {
    if(ele.is_null()) {
        return 0.0;
    }

    return ele.get<double>();
}

bool compare::is_total_revenue_equal() {
    auto query_str = IOUtil::read_file(ad_revenue_query_path);
    auto query_res = Req::make_a_www_query(v2_query_path, query_str);
    LOG(INFO) << query_res << "\n";
    auto res_js = json::parse(query_res);

    std::vector<int64_t> not_equal_products{};
    for(auto const& ele: res_js["data"]["facets"]) {
        auto ad_revenue_sum = get_zero_or_value(ele["est_ad_revenue__sum"]);
        auto revenue_sum = get_zero_or_value(ele["est_revenue__sum"]);
        auto total_revenue_sum = get_zero_or_value(ele["est_total_revenue__sum"]);
        std::stringstream total_revenue_ss; 
        std::stringstream act_revenue_ss;
        total_revenue_ss << std::fixed << std::setprecision(2) << total_revenue_sum;
        act_revenue_ss << std::fixed << std::setprecision(2) << (ad_revenue_sum + revenue_sum);

        if(total_revenue_ss.str() != act_revenue_ss.str()) {
            auto prod_id = ele["product_id"].get<int64_t>();
            LOG(ERROR) << "Ad Revenue: " << ad_revenue_sum;
            LOG(ERROR) << "Revenue: " << revenue_sum;
            LOG(ERROR) << "Total Revenue: " << total_revenue_sum;
            
            LOG(INFO) << "Total Revenue Precision: " << total_revenue_ss.str();
            LOG(INFO) << "Actual Revenue Precision: " << act_revenue_ss.str();
            not_equal_products.emplace_back(std::move(prod_id));
        }
    }

    if(not_equal_products.size() > 0) {
        LOG(ERROR) << "There are not equal products: ";
        for(auto const& prod_id: not_equal_products) {
            LOG(ERROR) << prod_id;
        }
        LOG(ERROR) << "\n";
    }

    return not_equal_products.size() == 0;
}