#include "utils/import_util.h"

#include <boost/beast/core/detail/base64.hpp>
#include <filesystem>

#include "api_accuracy/utils/io_util.h"
#include "http/http_util.h"
#include "json/json.hpp"
#include "pystring/pystring.h"
#include "utils/zepplin_mig_cfg.h"

namespace fs = std::filesystem;
using json = nlohmann::json;

std::string b64_encode(std::string const& raw_content) {
    auto len_ = raw_content.size();
    size_t encoded_size = boost::beast::detail::base64::encoded_size(len_);
    std::string base64_data;
    base64_data.resize(encoded_size);
    boost::beast::detail::base64::encode(&base64_data[0], &raw_content[0],
                                         len_);
    return base64_data;
}

DbsPath get_dbs_path(std::string const& path_) {
    std::vector<std::string> paths_arr;
    pystring::split(path_, paths_arr, "/");
    auto file_name = paths_arr[paths_arr.size() - 1];

    std::vector<std::string> file_names_arr;
    pystring::split(file_name, file_names_arr, "#");
    // 不是垃圾箱里面的文件
    if (file_names_arr[0] == "~Trash") {
        return DbsPath{"", "", false};
    }
    std::string dst_file_name{};
    std::stringstream ss;
    ss << "/Shared/";
    for (auto tmp_file_name_ : file_names_arr) {
        ss << tmp_file_name_ << "/";
    }

    auto final_name = ss.str();
    dst_file_name = final_name.substr(0, final_name.size() - 1);
    // Create dir
    auto pos = dst_file_name.find_last_of("/");
    auto dbs_path_ = dst_file_name.substr(0, pos);
    return DbsPath{dst_file_name, dbs_path_, true};
}

bool create_dbs_ws_dir(DbsPath const& dbs_path) {
    json create_dir_body;
    create_dir_body["path"] = dbs_path.dir;
    auto create_dir_body_str = create_dir_body.dump();
    std::string create_dir_post_res{};
    auto create_dir_res = HttpUtil::post_and_get_str(
        databricks_ws_host, ws_create_dir_url_path, headers,
        create_dir_body_str, create_dir_post_res);

    if (!create_dir_res) {
        std::cerr << create_dir_post_res << "\n";
        return false;
    }
    return true;
}

bool create_dbs_ws_file(DbsPath const& dbs_path, std::string const& base64_data) {
    // Create workspace file
    json body;

    body["path"] = dbs_path.path;
    body["content"] = base64_data;
    body["language"] = "PYTHON";
    body["overwrite"] = true;
    body["format"] = "JUPYTER";
    auto body_str = body.dump();

    std::string post_res{};
    auto import_res = HttpUtil::post_and_get_str(
        databricks_ws_host, ws_import_url_path, headers, body_str, post_res);

    if (!import_res) {
        std::cerr << post_res << "\n";
        return false;
    }
    return true;
}

bool ImportUtil::import_note_books(std::string const& note_path) {
    std::set<std::string> exist_paths{};
    for (auto const& entry : fs::directory_iterator(note_path)) {
        std::string path_ = entry.path();
        auto dbs_path = get_dbs_path(path_);
        if (!dbs_path.is_valid) {
            continue;
        }
        auto raw_content = IOUtil::read_file(path_);
        // Encode raw content to base64 encoded data
        auto base64_data = b64_encode(raw_content);
        // 如果exist_paths不包含这个dir，才需要创建
        // 创建不存在的dbs 目录
        if (exist_paths.find(dbs_path.dir) == exist_paths.end()) {
            bool res = create_dbs_ws_dir(dbs_path);
            exist_paths.insert(dbs_path.dir);
            if (!res) {
                return false;
            }
        }
        // 上载 dbs notebook
        bool create_file_res = create_dbs_ws_file(dbs_path, base64_data);
        if(!create_file_res) {
            return false;
        }
    }
    return true;
}