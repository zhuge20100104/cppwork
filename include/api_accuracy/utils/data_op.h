#ifndef _FREDRIC_DATA_OP_H_
#define _FREDRIC_DATA_OP_H_

#include "json/json.hpp"

using json = nlohmann::json;

struct data_op {
    data_op(const json& app_perf_result_);
    int get_apps_count();
    int get_data_chunks();
    json get_primary_key_list();

    json get_app_performance();
    json get_demographics();
    json get_product_meta_data();
    const json& app_perf_result;
};

#endif