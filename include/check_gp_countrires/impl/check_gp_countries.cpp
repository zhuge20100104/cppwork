#include "check_gp_countrires/check_gp_countries.h"
#include "http/http_util.h"
#include "pystring/pystring.h"
#include "check_gp_countrires/config.h"
#include "json/json.hpp"

#include <fstream>
#include <sstream>


using json = nlohmann::json;

bool send_request_query(const QueryEle& ele) {
    std::string query_path = ele.path;
    std::string query_body_path = QueryDataPath + ele.query_body_name + ".json";
    std::ifstream query_body_file(query_body_path);
    std::stringstream buffer;
    buffer << query_body_file.rdbuf();
    std::string query_body(buffer.str());

    std::vector<std::string> failed_countrires = {};
    for(auto&& country :GPCountries) {
        std::cout << "Country: [" << country << "]" << std::endl; 
        std::string body_str = pystring::replace(query_body, "{COUNTRY_CODE}", country);
        std::string result{};
        bool get_str_res = HttpUtil::post_and_get_str(Host, query_path, headers, body_str, result);

        if(!get_str_res) {
            failed_countrires.emplace_back(std::move(country));
        }
        auto res = json::parse(result);
        auto facet_len = res["data"]["facets"].size();
        if(facet_len == 0) {
            std::cout << "Country: [" << country <<  "]" << " has no data in DB!" << std::endl;
        }
    }
    return failed_countrires.size()  == 0;
}


