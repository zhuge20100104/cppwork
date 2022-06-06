#include "get_incident_file/get_incident_file.h"
#include "get_incident_file/config.h"
#include "http/http_util.h"
#include "json/json.hpp"
#include "yaml/yaml_util.h"

#include <pystring/pystring.h>

#include <fstream>
#include <iostream>


using json = nlohmann::json;

bool _get_component_list(json& component_list_res) {
    std::string component_list_str{};
    bool get_res = HttpUtil::get_str(status_io_host, component_list_url,
                                     headers, component_list_str);
    if (!get_res) {
        std::cerr << "Get component list failed!" << std::endl;
        return false;
    }

    component_list_res = json::parse(component_list_str);
    auto err_code = component_list_res["status"]["error"].get<std::string>();
    if (err_code == http::error_yes) {
        std::cerr << "Get component list failed!" << std::endl;
        return false;
    }
    return true;
}

std::string _make_container_id(const std::string& component_id,
                               const std::string& container_id) {
    std::ostringstream oss_id{};
    oss_id << component_id << "-" << container_id;
    return std::move(oss_id.str());
}

std::string _make_monitoring_category(const std::string& container_name) {
    auto category_src = pystring::lower(container_name);
    std::vector<std::string> res_vec{};
    if (category_src.find("_") != std::string::npos) {
        pystring::split(category_src, res_vec, "_");
    } else {
        pystring::split(category_src, res_vec, " ");
    }
    std::stringstream ss{};
    for (auto& ele : res_vec) {
        ss << ele;
        ss << "_";
    }
    auto category_name = ss.str();
    category_name = category_name.substr(0, category_name.size() - 1);
    return std::move(category_name);
}

std::string _make_concat_name(const std::string& prefix, const std::string& suffix) {
    std::stringstream ss;
    ss << prefix;
    ss << "_";
    ss << suffix;
    return std::move(ss.str());
}

bool _write_yaml_string_to_file(const std::string& yaml_str) {
    std::fstream fs{result_file_path, std::ios::out | std::ios::trunc};
    if (!fs.is_open()) {
        std::cerr << "Open file [" << result_file_path << "] failed"
                  << std::endl;
        return false;
    }
    fs << yaml_str;
    fs.close();
    return true;
}

objects_type _parse_component_list(const json& component_list_res) {
    objects_type objects_{};
    auto component_list = component_list_res["result"];
    for (auto&& component : component_list) {
        auto component_id = component["_id"].get<std::string>();
        auto component_name = component["name"].get<std::string>();
        auto containers = component["containers"];
        for (auto&& container : containers) {
            std::map<std::string, std::string> object{};
            auto container_id = container["_id"].get<std::string>();
            auto container_name = container["name"].get<std::string>();
            object["container_id"] =
                _make_container_id(component_id, container_id);
            object["container_name"] = container_name;
            auto category_prefix = _make_monitoring_category(component_name);
            auto category_suffix = _make_monitoring_category(container_name);
            object["monitoring_category"] = _make_concat_name(category_prefix, category_suffix);
            objects_.emplace_back(std::move(object));
        }
    }

    return std::move(objects_);
}

bool get_incident_file() {
    json component_list_res{};
    if (!_get_component_list(component_list_res)) {
        return false;
    }

    auto objects_ = _parse_component_list(component_list_res);

    auto yaml_str = yaml_util::convert_map_objects_to_yaml(objects_);

    if (!_write_yaml_string_to_file(yaml_str)) {
        return false;
    }
    return true;
}