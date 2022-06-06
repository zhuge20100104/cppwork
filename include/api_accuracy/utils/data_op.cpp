#include "api_accuracy/utils/data_op.h"

#include <cstddef>

#include "api_accuracy/utils/funcs.h"
#include "api_accuracy/utils/beans.h"

data_op::data_op(const json& app_perf_result_)
    : app_perf_result(app_perf_result_) {}

int data_op::get_apps_count() { return app_perf_result["products"].size(); }

int data_op::get_data_chunks() {
    auto products = app_perf_result["products"];
    int chunk_size = 0;
    for (auto&& product_ : products) {
        chunk_size += product_["app_performance"].size();
        chunk_size += product_["demographics"].size();
    }
    return chunk_size;
}

json data_op::get_primary_key_list() {
    auto products = app_perf_result["products"];
    json app_perf_dfs;
    for (auto&& product_ : products) {
        auto product_id = product_["product_id"].get<uint64_t>();
        auto product_name = product_["product_name"].get<std::string>();

        auto app_perfs = product_["app_performance"];

        json app_perf_info;
        app_perf_info["product"] = {{"product_id", product_id},
                                    {"product_name", product_name}};

        json app_perf_keys;

        for (auto&& app_perf : app_perfs) {
            json p_key = {
                {"date", app_perf["date"].get<std::string>()},
                {"country_code", app_perf["country_code"].get<std::string>()},
                {"device_code", app_perf["device_code"]}};

            app_perf_keys.emplace_back(std::move(p_key));
        }
        app_perf_info["key"] = std::move(app_perf_keys);
        app_perf_dfs.emplace_back(std::move(app_perf_info));
    }
    return std::move(app_perf_dfs);
}

json retrive_data_ending_zero(const json& app_perf) {
    json res;
    for (auto &&begin = app_perf.begin(), end = app_perf.end(); begin != end;
         ++begin) {
        auto key = begin.key();
        auto val = begin.value();
        if (val.is_number_float() &&
            (get_float_fraction(val.get<float>()) == 0.0)) {
            res[key] = (uint64_t)(val.get<float>());
        } else {
            res[key] = val;
        }
    }
    return std::move(res);
}

json data_op::get_app_performance() {
    auto products = app_perf_result["products"];
    json app_performances;
    for (auto&& product_ : products) {
        json app {
                {"product_id", product_["product_id"]},
                {"company_name", product_["company_name"]},
                {"publisher_name", product_["publisher_name"]},
                {"product_name", product_["product_name"]},
        };
        auto app_perfs = product_["app_performance"];
        json app_perfs_clean;
        for (auto&& app_perf : app_perfs) {
            app_perfs_clean.emplace_back(std::move(retrive_data_ending_zero(app_perf)));
        }
        app_performances[app.dump()] = app_perfs_clean;
    }
    return std::move(app_performances);
}

json data_op::get_demographics() {
    auto products = app_perf_result["products"];
    json demographics;

    for (auto&& product_ : products) {
        json app {
                {"product_id", product_["product_id"]},
                {"company_name", product_["company_name"]},
                {"publisher_name", product_["publisher_name"]},
                {"product_name", product_["product_name"]},
        };
        auto demos = product_["demographics"];
        json demos_clean;
        for (auto&& demo_ : demos) {
            demos_clean.emplace_back(std::move(retrive_data_ending_zero(demo_)));
        }
        demographics[app.dump()] = demos_clean;
    }
    return std::move(demographics);
}

json data_op::get_product_meta_data() {
    auto products = app_perf_result["products"];
    json app_metas;
    for (auto&& product_ : products) {
        product_.erase("app_performance");
        product_.erase("demographics");
        app_metas.emplace_back(std::move(product_));
    }
    return std::move(app_metas);
}