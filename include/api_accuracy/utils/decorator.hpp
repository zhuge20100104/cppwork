#ifndef _FREDRIC_DECORATOR_HPP_
#define _FREDRIC_DECORATOR_HPP_

#include <boost/date_time/posix_time/posix_time.hpp>

#include <chrono>
#include <functional>
#include <iostream>

#include "api_accuracy/test_cfg.h"
#include "api_accuracy/utils/beans.h"
#include "glog/logging.h"

//-------------------------------
// BEGIN decorator implementation
//-------------------------------

template <class>
struct decorator;


template <typename T>
void _write(const T& t){
	LOG(ERROR) << t << '\n';
}
 
template <typename T, typename ... Args>
void _write(const T& t, Args ... args){
	LOG(ERROR) << t << ',';
	_write(args...);
}

template <class R, class... Args>
struct decorator<R(Args...)> {
    decorator(std::function<R(Args...)> f) : f_(f) {}

    ReqResult operator()(Args... args) {
        R res;
        size_t total_time = 0;
        for (int i = 0; i < perf_retry_count; ++i) {
            json res_dic;
            boost::posix_time::ptime start;
            boost::posix_time::ptime end;
            try {
                LOG(INFO) << "try once..." << "\n";
                start = boost::posix_time::second_clock::local_time();
                res = f_(args...);
                end = boost::posix_time::second_clock::local_time();
                res_dic = json::parse(res);
            } catch(const std::exception& ex) {
               LOG(ERROR) << ex.what() << "\n";
               LOG(ERROR) << "URL: ";
               _write(args...);
               return ReqResult{false, res, 0};
            }

            // error in request, return directly
            auto err_it = res_dic.find("error");
            if(err_it != res_dic.end()) {
               LOG(ERROR) << res << "\n";
               return ReqResult{false, res, 0};
            }
            auto curr_time = (end - start).seconds();
            total_time += curr_time;
        }
        float avg_time = ((float)total_time) / ((float)perf_retry_count);
        return ReqResult{true, res, avg_time};
    }

    std::function<R(Args...)> f_;
};

template <class R, class... Args>
decorator<R(Args...)> make_decorator(R (*f)(Args...)) {
    return decorator<R(Args...)>(std::function<R(Args...)>(f));
}

#endif