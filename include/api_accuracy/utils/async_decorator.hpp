#ifndef _FREDRIC_ASYNC_DECORATOR_HPP_
#define _FREDRIC_ASYNC_DECORATOR_HPP_

#include <boost/date_time/posix_time/posix_time.hpp>

#include <chrono>
#include <functional>
#include <iostream>

#include "api_accuracy/test_cfg.h"
#include "api_accuracy/utils/beans.h"
#include "glog/logging.h"

#include <string>

#include "json/json.hpp"
using json = nlohmann::json;


//-------------------------------
// BEGIN decorator implementation
//-------------------------------

struct async_decorator {
    async_decorator(std::function<json(const std::string&)> f) : f_(f) {}

    AsyncReqResult operator()(const std::string& path) {
        std::string res;
        std::string report_url;
        size_t total_time = 0;
        for (int i = 0; i < perf_retry_count; ++i) {
            json res_dic;
            boost::posix_time::ptime start;
            boost::posix_time::ptime end;
            try {
                LOG(INFO) << "try once..." << "\n";
                start = boost::posix_time::second_clock::local_time();
                json async_res = f_(path);
                end = boost::posix_time::second_clock::local_time();
                res = async_res["result"].get<std::string>();
                report_url = async_res["report_url"].get<std::string>();
                res_dic = json::parse(res);
            } catch(const std::exception& ex) {
                LOG(ERROR) << ex.what() << "\n";
                LOG(ERROR) << "REPORT URL:";
                LOG(ERROR) << report_url;
                LOG(ERROR) << "URL: ";
                LOG(ERROR) << path;
                json js {{"result", res}, {"report_url", report_url}};
               return AsyncReqResult{false, std::move(js), 0};
            }

            // error in request, return directly
            auto err_it = res_dic.find("error");
            if(err_it != res_dic.end()) {
               LOG(ERROR) << res << "\n";
                json js {{"result", res}, {"report_url", report_url}};
               return AsyncReqResult{false, std::move(js), 0};
            }
            auto curr_time = (end - start).seconds();
            total_time += curr_time;
        }
        float avg_time = ((float)total_time) / ((float)perf_retry_count);
        json js {{"result", res}, {"report_url", report_url}};
        return AsyncReqResult{true, std::move(js), avg_time};
    }

    std::function<json(const std::string&)> f_;
};

async_decorator make_async_decorator(json (*f)(const std::string&)) {
    return async_decorator(std::function<json(const std::string&)>(f));
}

#endif