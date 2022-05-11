#include "api_accuracy/utils/req.h"
#include "http/http_util.h"
#include "api_accuracy/test_cfg.h"
#include "http/url_parse.h"
#include "api_accuracy/utils/token_get.h"

#include <glog/logging.h>


#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time.hpp>

#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>

std::string Req::make_a_www_query(const std::string& path, const std::string& body) {
    std::string www_res{};
    std::string www_token = "Bearer " + get_www_token();
    www_headers.insert({"Authorization", www_token});
    bool get_www_res = HttpUtil::post_and_get_str(www_host, path, www_headers, body, www_res);
    if(!get_www_res) {
        LOG(ERROR) << "Get WWW result failure" << "\n";
        return "";
    }
    return std::move(www_res);
}

std::string Req::make_a_api_query(const std::string& path) {
    std::string api_res{};
    bool get_api_res = HttpUtil::get_str(api_host, path, api_headers, api_res);
    if(!get_api_res) {
        LOG(ERROR) << "Get api result failure" << "\n";
        return "";
    }
    return std::move(api_res);
}

std::string Req::make_a_async_api_query(const std::string& path) {
    std::string api_res{};
    bool get_api_res = HttpUtil::get_str(async_api_host, path, async_api_headers, api_res);
    if(!get_api_res) {
        LOG(ERROR) << "Get async api result failure" << "\n";
        return "";
    }

    auto async_status_res = json::parse(api_res);
    if(async_status_res["code"].get<int>() != 200) {
        return "";
    }

    // auto report_url
    auto report_id = async_status_res["report_id"].get<std::string>();
    std::stringstream rep_path_ss;
    rep_path_ss << report_path << report_id;

    std::string r_report;
    bool get_api_data_res = HttpUtil::get_str(async_api_host, rep_path_ss.str(), async_api_headers, r_report);
    if(!get_api_data_res) {
        LOG(ERROR) << "Get async api data failure" << "\n";
        return "";
    }

    auto report_res = json::parse(r_report);
    int total_delay {0};

    while(((report_res.find("report_status") == report_res.end())  || (report_res["report_status"].get<std::string>() != "done")) && (total_delay < max_async_timeout)) {
        get_api_data_res = HttpUtil::get_str(async_api_host, rep_path_ss.str(), async_api_headers, r_report);
        if(!get_api_data_res) {
            LOG(ERROR) << "Get async api data failure" << "\n";
            return "";
        }
        report_res = json::parse(r_report);
        boost::this_thread::sleep(boost::posix_time::seconds(sleep_interval));
        ++total_delay;
    }

    if((report_res.find("report_status") == report_res.end()) || (report_res["report_status"].get<std::string>() != "done")) {
        LOG(ERROR) << "Report is still not ready after " << max_async_timeout * sleep_interval << " ...";
        LOG(ERROR) << r_report;
        return "";
    }
           
    return std::move(r_report);
}

void Req::make_a_async_api_query_and_get_report_url(const std::string& path, json &res) {
    
    auto start = boost::posix_time::microsec_clock::local_time();
    auto req_res = Req::make_a_async_api_query_and_get_report_url(path);
    auto end = boost::posix_time::microsec_clock::local_time();
    auto millseconds = (end - start).total_milliseconds();
    bool is_success = true;
    try {
        auto res_js = json::parse(req_res["result"].get<std::string>());
    } catch(std::exception const& ex) {
        LOG(ERROR) << ex.what() << "\n";
        is_success = false;
    }
    res["milliseconds"] = millseconds;
    res["success"] = is_success;
}

 json Req::make_a_async_api_query_and_get_report_url(const std::string& path) {
    std::string api_res{};
    bool get_api_res = HttpUtil::get_str(async_api_host, path, async_api_headers, api_res);
    if(!get_api_res) {
        LOG(ERROR) << "Get async api result failure" << "\n";
        json res {{"result", ""}, {"report_url", ""}};
        return std::move(res);
    }

    auto async_status_res = json::parse(api_res);
    if(async_status_res["code"].get<int>() != 200) {
        LOG(ERROR) << api_res << "\n";
        json res {{"result", ""}, {"report_url", ""}};
        return std::move(res);
    }

    auto report_id = async_status_res["report_id"].get<std::string>();
    std::stringstream rep_path_ss;
    rep_path_ss << report_path << report_id;

    std::stringstream rep_url_ss;
    rep_url_ss << "https://" << async_api_host << "/" << rep_path_ss.str();
    auto report_url = rep_url_ss.str();
    std::string r_report;
    bool get_api_data_res = HttpUtil::get_str(async_api_host, rep_path_ss.str(), async_api_headers, r_report);
    if(!get_api_data_res) {
        LOG(ERROR) << "Get async api data failure" << "\n";
        json res {{"result", ""}, {"report_url", report_url}};
        return std::move(res);
    }

    auto report_res = json::parse(r_report);
    int total_delay {0};

    while(((report_res.find("report_status") == report_res.end())  || (report_res["report_status"].get<std::string>() != "done")) && (total_delay < max_async_timeout)) {
        get_api_data_res = HttpUtil::get_str(async_api_host, rep_path_ss.str(), async_api_headers, r_report);
        if(!get_api_data_res) {
            LOG(ERROR) << "Get async api data failure" << "\n";
            json res {{"result", ""}, {"report_url", report_url}};
            return std::move(res);
        }
        report_res = json::parse(r_report);
        boost::this_thread::sleep(boost::posix_time::seconds(sleep_interval));
        ++total_delay;
    }

    // != "done", report 没有意义，直接返回空
    if((report_res.find("report_status") == report_res.end()) || (report_res["report_status"].get<std::string>() != "done")) {
        LOG(ERROR) << "Report is still in progress, After: " << (max_async_timeout * sleep_interval) << "..." << "\n";
        json res {{"result", ""}, {"report_url", report_url}};
        return std::move(res);
    }
           
    json res {{"result", r_report}, {"report_url", report_url}};
    return std::move(res);
}

std::string Req::make_a_zipped_query(const std::string& path) {
    std::string api_res{};
    bool get_api_res = HttpUtil::get_zipped_str(api_host, path, zipped_api_headers, api_res);
    if(!get_api_res) {
        LOG(ERROR) << "Get api result failure" << "\n";
        return "";
    }
    return std::move(api_res);
}

std::string Req::make_a_async_zipped_query(const std::string& report_url) {
    std::string api_res{};
    url_parse parse_ {report_url};
    parse_.parse_host_and_path();
    bool get_api_res = HttpUtil::get_zipped_str(parse_.get_host(), parse_.get_path(), zipped_api_headers, api_res);
    if(!get_api_res) {
        LOG(ERROR) << "Get zipped async api result failure" << "\n";
        return "";
    }
    return std::move(api_res);
}

