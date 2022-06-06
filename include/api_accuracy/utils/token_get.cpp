#include "api_accuracy/utils/token_get.h"
#include "http/http_util.h"
#include "json/json.hpp"
#include "glog/logging.h"

using json = nlohmann::json;

#include <map>

std::string get_www_token() {
    std::map<std::string, std::string> token_headers {
        {"Content-Type", "application/x-www-form-urlencoded"},
        {"Postman-Token", "63f2ffa4-0a0a-43b3-ac46-404480ac6644"},
        {"authorization", "Basic bXMtZmU6ZVY2elpKV1hRckVz"},
        {"cache-control", "no-cache"},
        {"user-agent", "AAppC34JTB1NDTWD:4.2"}
    };

    std::string host = "api.appannie.com";
    std::string auth_path = "/oauth2/access_token";
    std::string body = "username=fzhu%40appannie.com&password=Lily!870104&grant_type=password&client_secret=5936810c7268c0241c5b48ad6c2f082f15029ff2&client_id=79499a6f0ceb17a01ce0";

    std::string token_res;
    HttpUtil::post_and_get_str(host, auth_path, token_headers, body, token_res);
    auto res = json::parse(token_res);
    auto token_ = res["access_token"].get<std::string>(); 

    LOG(INFO) << "WWW Token: " << token_ << "\n";
    return token_;
}