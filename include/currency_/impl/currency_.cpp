#include "currency_/currency_.h"

#include <iostream>
#include <string>

#include "currency_/currency_obj.h"
#include "json/json.hpp"

using json = nlohmann::json;

sf_connection currency_util::conn_{conn_str};

bool currency_util::check_currencies() {
    auto currency_query_sql =
        R"(select product_key,locale, top_in_app_list from  AA_INTELLIGENCE_PRODUCTION.ADL_MASTER.DIM_PRODUCT_LOCALIZED_DETAIL_V1_CLUSTER_BY_PRODUCT_KEY 
    where market_code='apple-store' 
    and scraped_time='2021-09-02' 
    and top_in_app_list  is not null
    limit 10000;)";

    auto res = conn_.exec_raw_query(currency_query_sql);
    std::vector<currency> currencies{};

    const std::string null_value = "null";
    while (res.next()) {
        auto product_key = res.get<std::string>(0, null_value);
        auto locale = res.get<std::string>(1, null_value);
        auto top_in_apps_raw = res.get<std::string>(2, null_value);
        auto top_in_apps = json::parse(top_in_apps_raw);

        for (auto&& app : top_in_apps) {
            auto name = app["name"].get<std::string>();
            auto price_str = app["price"].get<std::string>();
            double price{-1};
            try {
                price = std::stod(price_str);
            } catch (const std::exception& ex) {
                std::cerr << "Price check failed here, "
                          << " product_key: " << product_key
                          << " locale: " << locale << " price: " << price
                          << " error: " << ex.what() << std::endl;
            }
            auto raw_price_str = app["raw_price_string"].get<std::string>();
            currency curr_{product_key, name, raw_price_str, price, locale};
            currencies.emplace_back(std::move(curr_));
        }
    }

    for (auto&& curr_ : currencies) {
        if ((!curr_.is_sign_valid()) || (!curr_.is_price_valid())) {
            std::cout << "Product: " << curr_.product_key << ", " << curr_.name
                      << "'s currency is not valid, locale: " << curr_.locale
                      << " price is " << curr_.price << std::endl;
            return false;
        }
    }
    return true;
}