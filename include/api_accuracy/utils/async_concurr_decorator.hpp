#ifndef _FREDRIC_ASYNC_CONCURR_DECORATOR_HPP_
#define _FREDRIC_ASYNC_CONCURR_DECORATOR_HPP_

#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <chrono>
#include <functional>
#include <algorithm>
#include <iostream>
#include <string>

#include "api_accuracy/test_cfg.h"
#include "api_accuracy/utils/beans.h"
#include "glog/logging.h"
#include "json/json.hpp"
using json = nlohmann::json;

//-------------------------------
// BEGIN decorator implementation
//-------------------------------

struct async_concurr_decorator {
    async_concurr_decorator(std::function<void(const std::string&, json&)> f)
        : f_(f) {}

    AsyncConCurrResult operator()(const std::string& path) {
        boost::asio::thread_pool pool{(std::size_t)(async_concurr_count)};

        std::vector<json> async_results_;
        async_results_.resize(async_concurr_count);
        for (int i = 0; i < async_concurr_count; ++i) {
            boost::asio::post(pool, std::bind(f_, std::cref(path),
                                              std::ref(async_results_[i])));
        }
        pool.join();

        auto fail_count = 0;
        float max_time = 0;
        float min_time = std::numeric_limits<float>::max();
        float avg_time = 0;

        for(auto&& res_js: async_results_) {
            auto millseconds_ = res_js["milliseconds"].get<uint64_t>();
            auto is_success_ = res_js["success"].get<bool>();
            if(!is_success_) {
                ++fail_count;
            }
            if(millseconds_ < min_time) {
                min_time = millseconds_;
            }
            if(millseconds_ > max_time) {
                max_time = millseconds_;
            }
            avg_time += millseconds_;
        }
        // 不能只用成功的数，如果只用成功的，全失败的话，就会overflow
        avg_time = avg_time/((float)(async_concurr_count));
        AsyncConCurrResult res {max_time, min_time, avg_time, async_concurr_count, fail_count};
        return std::move(res);
    }

    std::function<void(const std::string&, json&)> f_;
};

async_concurr_decorator make_async_concurr_decorator(
    void (*f)(const std::string&, json&)) {
    return async_concurr_decorator(std::function<void(const std::string&, json&)>(f));
}

#endif
