#include "tasks/task_summary.h"
#include "utils/const.h"

#include <iostream>


task_summary::task_summary(const std::vector<std::string>& task_infos) {

    json results_j {};
    for(auto&& task_info: task_infos) {
        auto task_info_js = json::parse(task_info);
        all_results_.push_back(task_info_js);
    }

    auto i = 0;

    int min_req_time = MIN_TIME_BOUND;
    int max_req_time = MAX_TIME_BOUND;

    for(auto&& task_info_js: all_results_) {
        auto requests_js = task_info_js["requests"]["single"];
        for(auto &&req_it = requests_js.begin(), end = requests_js.end();
        req_it != end; ++req_it) {
            auto req_name = req_it.key();
            auto req_value = req_it.value();

            if(req_value["min_request_time"].get<int>() < min_req_time) {
                min_req_time = req_value["min_request_time"].get<int>();
                results_j[req_name]["min_request_time"] =  min_req_time;
            }

            if(req_value["max_request_time"].get<int>() > max_req_time) {
                max_req_time = req_value["max_request_time"].get<int>();
                results_j[req_name]["max_request_time"] = max_req_time;
            }
            // 第一次， 赋值results_j
            if(i == 0) {
                results_j[req_name]["url"] = req_value["url"].get<std::string>();
                results_j[req_name]["method"] =  req_value["method"].get<std::string>();
                results_j[req_name]["body"] = req_value["body"].get<std::string>();
                results_j[req_name]["headers"] = req_value["headers"].get<std::map<std::string, std::string>>();

                results_j[req_name]["avg_request_time"] =  req_value["avg_request_time"].get<int>();
                results_j[req_name]["through_out"] =  req_value["through_out"].get<int>();
                // 不是第一次，直接用 += 运算符
            } else {

                auto old_avg = results_j[req_name]["avg_request_time"].get<int>();
                results_j[req_name]["avg_request_time"] = old_avg + req_value["avg_request_time"].get<int>();

                auto old_through_out = results_j[req_name]["through_out"].get<int>();
                results_j[req_name]["through_out"] = old_through_out + req_value["through_out"].get<int>();
            }
        }
        ++i;
    }

    for(auto &&req_it = results_j.begin(), end = results_j.end();
        req_it != end; ++req_it) {
            auto req_name = req_it.key();

            auto avg_req_time = results_j[req_name]["avg_request_time"].get<int>();
            results_j[req_name]["avg_request_time"] = avg_req_time/i;
    }

    summary_j["requests"]["single"] = results_j;
}


void task_summary::dump_summary_results() {
    std::string res = summary_j.dump();
    std::cerr << res << std::endl;
}