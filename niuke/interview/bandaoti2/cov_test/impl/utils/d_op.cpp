#include "utils/d_op.h"
#include "utils/bdp_dbr_cfg.h"

#include "glog/logging.h"

#include "json/json.hpp"
#include "df/df.h"
#include "arr_/arr_.h"
#include "pystring/pystring.h"

#include <algorithm>
#include <fstream>
#include <set>


using json = nlohmann::json;

std::vector<std::string> d_op::get_bdp_bucket_list() {
    std::shared_ptr<arrow::Table> tb{};
    ArrowUtil::read_csv(bdp_csv_path.c_str(), tb);
    auto const& tb_ = *tb;  
    auto const& policy_conts_chunk_arr = tb_.GetColumnByName("content");
    auto const& policies_js = ArrowUtil::chunked_array_to_str_vector(policy_conts_chunk_arr);
    
    std::vector<std::string> policies{};
    for(auto const& policy_js: policies_js) {
        auto const& policy_ob = json::parse(policy_js);
        auto const& stats = policy_ob["Statement"];
        for(auto const& stat: stats) {
            auto eles = stat["Resource"];
            for(auto ele: eles) {
                policies.emplace_back(ele.get<std::string>());
            }
        }
    }
    return policies;
}

std::vector<std::string> d_op::get_databricks_bucket_list() {
    std::vector<std::string> res_policies{};
    std::shared_ptr<arrow::Table> tb{};
    ArrowUtil::read_csv(db_csv_path.c_str(), tb);
    auto const& tb_ = *tb;  
    auto const& db_bulkets_chunk_arr = tb_.GetColumnByName("S3 bucket list");  
    auto policies_js = ArrowUtil::chunked_array_to_str_vector(db_bulkets_chunk_arr);
    for(auto const& policy: policies_js) {
        if(policy != "") {
            res_policies.emplace_back(std::move(policy));
        }
    }
    return res_policies;
}

std::vector<std::string> d_op::get_missing_bucket_list(std::vector<std::string> const& bdp_final, std::vector<std::string> const& db_final) {
    std::vector<std::string> missing_buckets;
    for(auto const& bdp_bucket: bdp_final) {
        bool is_in_db {false};
        for(auto const& db_bucket: db_final) {
            if(bdp_bucket.find(db_bucket)!=std::string::npos) {
                is_in_db = true;
                break;
            }
        }
        if(!is_in_db) {
            missing_buckets.emplace_back(bdp_bucket);
        }
    }
    return missing_buckets;
}

std::vector<std::string> d_op::fx_missing_results(std::vector<std::string> const& missing_results) {
    // std::set insert自动去重
    std::set<std::string> final_missing_results;
    
    std::transform(missing_results.begin(), missing_results.end(), std::inserter(final_missing_results, final_missing_results.begin()), [](auto const& missing_bucket){
        auto tmp = pystring::replace(missing_bucket, "arn:aws:s3:::", "");
        if(tmp.find("/*") == tmp.size()-2) {
            tmp = tmp.substr(0, tmp.size()-2);    
        }
        return tmp;
    });

    std::vector<std::string> results{}; 
    results.resize(final_missing_results.size());
    std::transform(final_missing_results.begin(), final_missing_results.end(), results.begin(), [](auto const& str){
        return str;
    });
    return results;
}

bool d_op::write_to_csv(std::vector<std::string> const& missing_final) {
    CLDataFrame df;
    std::vector<unsigned long> idxes{};
    idxes.reserve(missing_final.size());
    for(unsigned long i=1; i<=missing_final.size(); ++i) {
        idxes.emplace_back(std::move(i));
    }
    
    df.load_data(std::move(idxes),
        std::make_pair("missing_bulkets", std::move(missing_final)));

    std::fstream fs {result_csv_path, std::ios::out | std::ios::trunc};
    if(!fs.is_open()) {
        LOG(ERROR) << "Open file failed" << "\n";
        return false;
    }
    
    df.write<std::ostream, std::string>(fs, hmdf::io_format::csv2, true);
    fs.close();
    return true;
}