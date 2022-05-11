#include "check_api/check_api.h"
#include "http/http_util.h"
#include "json/json.hpp"

#include <map>
#include <string>
#include <sstream>

using json = nlohmann::json;

bool check_top_apps(const std::vector<std::string>& countries) {
   
    std::string host = "api.appannie.com";
    bool res = true;
    for (auto&& country : countries) {
        std::stringstream ss;
        ss << "/v1.3/intelligence/apps/google-play/ranking?countries=";
        ss << country;
        ss <<  "&categories=OVERALL&device=android&start_date=2021-08-01";
        std::string path = ss.str();
        std::map<std::string, std::string> headers{
            {"Authorization",
             BEARER_TOKEN}};
        std::string result{};
        bool get_str_res = HttpUtil::get_str(host, path, headers, result);
        if(get_str_res == true) {
            auto res_body = json::parse(result);
            auto free_size = res_body["list"]["free"].size();
            if(free_size > 0) {
                std::cout << "Get [" << path <<  "] success" << std::endl;
            }else {
                std::cerr << "Get [" << path <<  "] failed, no result" << std::endl;
                res = false;
            }
        } else {
            std::cerr << "Get [" << path <<  "] failed" << std::endl;
            res = false;
        }
    }
    return res;
}

bool check_v12_app_rank_history(const std::vector<std::string>& countries) {
    std::string host = "api.appannie.com";
    bool res = true;
    for (auto&& country : countries) {
        std::stringstream ss;
        ss << "/v1.2/intelligence/apps/google-play/app/20600000009072/history?countries=";
        ss << country;
        ss <<  "&feeds=downloads&device=android&start_date=2021-08-01";
        std::string path = ss.str();
        std::map<std::string, std::string> headers{
            {"Authorization",
             BEARER_TOKEN}};
        std::string result{};
        bool get_str_res = HttpUtil::get_str(host, path, headers, result);
        if(get_str_res == true) {
            auto res_body = json::parse(result);
            auto list_size = res_body["list"].size();
            if(list_size > 0) {
                bool actual_no_na = false;
                for(int i = 0; i< list_size; ++i) {
                    if(res_body["list"][i]["estimate"] != "N/A") {
                        actual_no_na = true;
                        break;
                    }
                }
                // 有一个全NA的，就认为res false
                if(actual_no_na == false) {
                    res = false;
                    std::cerr << "Get [" << path <<  "] failed, N/A result" << std::endl;
                } else {
                    std::cout << "Get [" << path <<  "] success" << std::endl;
                }
            }else {
                std::cerr << "Get [" << path <<  "] failed, no result" << std::endl;
                res = false;
            }
        } else {
            std::cerr << "Get [" << path <<  "] failed" << std::endl;
            res = false;
        }
    }
    return res;
}

bool check_top_publisher(const std::vector<std::string>& countries) {
    std::string host = "api.appannie.com";
    bool res = true;
    for (auto&& country : countries) {
        std::stringstream ss;
        ss << "/v1.3/intelligence/apps/google-play/publisher-ranking?countries=";
        ss << country;
        ss <<  "&categories=OVERALL&device=android&start_date=2021-08-01";
        std::string path = ss.str();
        std::map<std::string, std::string> headers{
            {"Authorization",
             BEARER_TOKEN}};
        std::string result{};
        bool get_str_res = HttpUtil::get_str(host, path, headers, result);
        if(get_str_res == true) {
            auto res_body = json::parse(result);
            auto free_size = res_body["list"]["free"].size();
            if(free_size > 0) {
                std::cout << "Get [" << path <<  "] success" << std::endl;
            }else {
                std::cerr << "Get [" << path <<  "] failed, no result" << std::endl;
                res = false;
            }
        } else {
            std::cerr << "Get [" << path <<  "] failed" << std::endl;
            res = false;
        }
    }
    return res;
}

bool check_publisher_history(const std::vector<std::string>& countries) {
    std::string host = "api.appannie.com";
    bool res = true;
    for (auto&& country : countries) {
        std::stringstream ss;
        ss << "/v1.3/intelligence/apps/google-play/publisher/20200001443478/history?countries=";
        ss << country;
        ss <<  "&categories=OVERALL&device=android&start_date=2021-08-01";
        std::string path = ss.str();
        std::map<std::string, std::string> headers{
            {"Authorization",
             BEARER_TOKEN}};
        std::string result{};
        bool get_str_res = HttpUtil::get_str(host, path, headers, result);
        if(get_str_res == true) {
            auto res_body = json::parse(result);
            auto list_size = res_body["list"].size();
            if(list_size > 0) {
                bool actual_no_na = false;
                for(int i = 0; i< list_size; ++i) {
                    if(res_body["list"][i]["estimate"] != "N/A") {
                        actual_no_na = true;
                        break;
                    }
                }
                // 有一个全NA的，就认为res false
                if(actual_no_na == false) {
                    res = false;
                    std::cerr << "Get [" << path <<  "] failed, N/A result" << std::endl;
                } else {
                    std::cout << "Get [" << path <<  "] success" << std::endl;
                }
            }else {
                std::cerr << "Get [" << path <<  "] failed, no result" << std::endl;
                res = false;
            }
        } else {
            std::cerr << "Get [" << path <<  "] failed" << std::endl;
            res = false;
        }
    }
    return res;
}


bool check_top_apps_mobile(const std::vector<std::string>& countries) {
    std::string host = "api.appannie.com";
    bool res = true;
    for (auto&& country : countries) {
        std::stringstream ss;
        ss << "/v1.2/mobile/intelligence/apps/google-play/ranking?countries=";
        ss << country;
        ss <<  "&categories=OVERALL&device=android&start_date=2021-08-01";
        std::string path = ss.str();
        std::map<std::string, std::string> headers{
            {"Authorization",
             BEARER_TOKEN}};
        std::string result{};
        bool get_str_res = HttpUtil::get_str(host, path, headers, result);
        if(get_str_res == true) {
            auto res_body = json::parse(result);
            auto list_size = res_body["list"].size();
            if(list_size > 0) {
                std::cout << "Get [" << path <<  "] success" << std::endl;
            }else {
                std::cerr << "Get [" << path <<  "] failed, no result" << std::endl;
                res = false;
            }
        } else {
            std::cerr << "Get [" << path <<  "] failed" << std::endl;
            res = false;
        }
    }
    return res;
}

bool check_top_publisher_mobile(const std::vector<std::string>& countries) {
    std::string host = "api.appannie.com";
    bool res = true;
    for (auto&& country : countries) {
        std::stringstream ss;
        ss << "/v1.2/mobile/intelligence/apps/google-play/publisher-ranking?countries=";
        ss << country;
        ss <<  "&categories=OVERALL&device=android&start_date=2021-08-01";
        std::string path = ss.str();
        std::map<std::string, std::string> headers{
            {"Authorization",
             BEARER_TOKEN}};
        std::string result{};
        bool get_str_res = HttpUtil::get_str(host, path, headers, result);
        if(get_str_res == true) {
            auto res_body = json::parse(result);
            auto list_size = res_body["list"].size();
            if(list_size > 0) {
                std::cout << "Get [" << path <<  "] success" << std::endl;
            }else {
                std::cerr << "Get [" << path <<  "] failed, no result" << std::endl;
                res = false;
            }
        } else {
            std::cerr << "Get [" << path <<  "] failed" << std::endl;
            res = false;
        }
    }
    return res;
}


bool check_app_rank_history_mobile(const std::vector<std::string>& countries) {
    std::string host = "api.appannie.com";
    bool res = true;
    for (auto&& country : countries) {
        std::stringstream ss;
        ss << "/v1.2/intelligence/apps/google-play/app/20600000009072/history?countries=";
        ss << country;
        ss <<  "&feeds=downloads&device=android&start_date=2021-08-01";
        std::string path = ss.str();
        std::map<std::string, std::string> headers{
            {"Authorization",
             BEARER_TOKEN}};
        std::string result{};
        bool get_str_res = HttpUtil::get_str(host, path, headers, result);
        if(get_str_res == true) {
            auto res_body = json::parse(result);
            auto list_size = res_body["list"].size();
            if(list_size > 0) {
                bool actual_no_na = false;
                for(int i = 0; i< list_size; ++i) {
                    if(res_body["list"][i]["estimate"] != "N/A") {
                        actual_no_na = true;
                        break;
                    }
                }
                // 有一个全NA的，就认为res false
                if(actual_no_na == false) {
                    res = false;
                    std::cerr << "Get [" << path <<  "] failed, N/A result" << std::endl;
                } else {
                    std::cout << "Get [" << path <<  "] success" << std::endl;
                }
            }else {
                std::cerr << "Get [" << path <<  "] failed, no result" << std::endl;
                res = false;
            }
        } else {
            std::cerr << "Get [" << path <<  "] failed" << std::endl;
            res = false;
        }
    }
    return res;
}


bool check_publisher_history_mobile(const std::vector<std::string>& countries) {
    std::string host = "api.appannie.com";
    bool res = true;
    for (auto&& country : countries) {
        std::stringstream ss;
        ss << "/v1.2/mobile/intelligence/apps/google-play/publisher/20200001443478/history?countries=";
        ss << country;
        ss <<  "&categories=OVERALL&device=android&start_date=2021-08-01";
        std::string path = ss.str();
        std::map<std::string, std::string> headers{
            {"Authorization",
             BEARER_TOKEN}};
        std::string result{};
        bool get_str_res = HttpUtil::get_str(host, path, headers, result);
        if(get_str_res == true) {
            auto res_body = json::parse(result);
            auto list_size = res_body["list"].size();
            if(list_size > 0) {
                bool actual_no_na = false;
                for(int i = 0; i< list_size; ++i) {
                    if(res_body["list"][i]["estimate"] != "N/A") {
                        actual_no_na = true;
                        break;
                    }
                }
                // 有一个全NA的，就认为res false
                if(actual_no_na == false) {
                    res = false;
                    std::cerr << "Get [" << path <<  "] failed, N/A result" << std::endl;
                } else {
                    std::cout << "Get [" << path <<  "] success" << std::endl;
                }
            }else {
                std::cerr << "Get [" << path <<  "] failed, no result" << std::endl;
                res = false;
            }
        } else {
            std::cerr << "Get [" << path <<  "] failed" << std::endl;
            res = false;
        }
    }
    return res;
}