#include "gp_store/gp_store_opener.h"
#include "json/json.hpp"
#include "http/http_util.h"

#include <fstream>
#include <sstream>

using json = nlohmann::json;

bool gp_store_opener::get_a_country(const std::string& country_code) {
    std::string host = "play.google.com";
    std::stringstream ss;
    ss << "/store/apps/details?id=com.facebook.katana&hl=";
    ss << country_code;
    std::string path = ss.str();

    std::string result_name = "./result/"+ country_code + ".html";
    bool download_res = HttpUtil::get_file(host, path, result_name);

    std::ifstream fs {result_name};
    std::stringstream buffer;
    buffer << fs.rdbuf();
    std::string play_store_str = buffer.str();
    auto check_str_res = play_store_str.find("com.facebook.katana") >= 0;

    return download_res && check_str_res;
}


std::vector<std::string> gp_store_opener::read_all_language_code() {
    std::ifstream country_mapping_file("../gp_country_list.json");
    std::stringstream buffer;
    buffer << country_mapping_file.rdbuf();
    std::string country_mapping_str = buffer.str();

    auto country_mapping = json::parse(country_mapping_str);
    std::vector<std::string> countrires{};

    for(auto&& country_ele: country_mapping) {
        auto& value =  country_ele["value"];
        countrires.emplace_back(std::move(value));
    }
    return std::move(countrires);
}