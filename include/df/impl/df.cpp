#include "df/df.h"

#include <glog/logging.h>

CDataFrame df_op::convert_json_to_df(const json& js, const std::vector<std::string>& pri_keys_) {
    CDataFrame::set_thread_level(10);
    CDataFrame df;

    unsigned long idx = 1ul;
    std::vector<unsigned long> ulidxs{};

    std::vector<std::string> keys_ = get_df_keys(js);
    if(keys_.size() == 0) {
        return df;
    }
    
    std::map<std::string, std::vector<json>> columns {};

    for (auto&& ele_js : js) {
        std::string key {};
        for(auto column_key: keys_) {
            if(columns.find(column_key) == columns.end()) {
                std::vector<json> tmp_v {ele_js[column_key]};
                columns[column_key] = std::move(tmp_v);
            } else {
                columns[column_key].emplace_back(std::move(ele_js[column_key]));
            }   
            // No primary keys specified, all columns are considered as primary keys
            if(pri_keys_.size() == 0) {
                key +=  ele_js[column_key].dump();
            } else {
                auto key_it_ = std::find(pri_keys_.begin(), pri_keys_.end(), column_key);
                if(key_it_ != pri_keys_.end()) {
                    key +=  ele_js[column_key].dump();
                }
            }
        }

        if(columns.find(Keys) == columns.end()) {
            std::vector<json> tmp_v {json(key)};
            columns[Keys] = std::move(tmp_v);
        } else {
            columns[Keys].emplace_back(std::move(json(key)));
        }

        ulidxs.emplace_back(idx++);
    }
    
    df.load_index(ulidxs.begin(), ulidxs.end());
    for(auto&& key: keys_) {
        df.load_column<json>(key.c_str(), {columns[key].begin(), columns[key].end()}, hmdf::nan_policy::pad_with_nans);
    }

    df.load_column<json>(Keys.c_str(), {columns[Keys].begin(), columns[Keys].end()}, hmdf::nan_policy::pad_with_nans);
    return df;
}

std::vector<std::string> df_op::get_df_keys(const json& js) {
    std::vector<std::string> keys_{};
    if(js.size() == 0) {
        LOG(ERROR) << "Json list size is zero, empty list!!" << "\n";
        return keys_;
    }

    auto ele_0 = js[0];
    for (auto &&begin = ele_0.begin(), end = ele_0.end(); begin != end; ++begin) {
        auto key = begin.key();
        keys_.emplace_back(key);
    }
    return keys_;
}

CDataFrame df_op::remove_duplicate(const CDataFrame& df, const std::vector<std::string>& keys_) {
    auto size_ = keys_.size();
    if(size_ == 1) {
        return df.remove_duplicates<json>(keys_[0].c_str(), false, hmdf::remove_dup_spec::keep_none);
    } else if(size_ == 2) {
        return df.remove_duplicates<json, json>(keys_[0].c_str(), keys_[1].c_str(), false, hmdf::remove_dup_spec::keep_none);
    } else if(size_ == 3) {
        return df.remove_duplicates<json, json, json>(keys_[0].c_str(), keys_[1].c_str(),keys_[2].c_str(), false, hmdf::remove_dup_spec::keep_none);
    } else if(size_ == 4) {
        return df.remove_duplicates<json, json, json, json>(keys_[0].c_str(), keys_[1].c_str(),keys_[2].c_str(), keys_[3].c_str(), false, hmdf::remove_dup_spec::keep_none);
    } else if(size_ == 5) {
        return df.remove_duplicates<json, json, json, json, json>(keys_[0].c_str(), keys_[1].c_str(),keys_[2].c_str(), keys_[3].c_str(), keys_[4].c_str(), false, hmdf::remove_dup_spec::keep_none);
    } else if(size_ == 6) {
        return df.remove_duplicates<json, json, json, json, json, json>(keys_[0].c_str(), keys_[1].c_str(),keys_[2].c_str(), keys_[3].c_str(), keys_[4].c_str(), keys_[5].c_str() , false, hmdf::remove_dup_spec::keep_none);
    } else {
        throw std::runtime_error("Not supported argument length, greater than 6!");
    }
}

bool df_op::write_to_csv(const CDataFrame& df, const std::string& csv_file_name) {
    std::fstream fs {csv_file_name, std::ios::out | std::ios::trunc};
    if(!fs.is_open()) {
        LOG(ERROR) << "Open file failed" << "\n";
        return false;
    }
    
    df.write<std::ostream, json>(fs, hmdf::io_format::csv2, true);
    fs.close();
    return true;
}