#include "tasks/task_launcher.h"

#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>
#include <functional>
#include <iostream>
#include <sstream>
#include <chrono>

#include "http/http_util.h"
#include "utils/const.h"
#include "tasks/url_parse.h"

using json = nlohmann::json;

task_launcher::task_launcher(const std::string& task_info) {
    auto task_info_js = json::parse(task_info);
    auto thread_count_ = task_info_js["thread_count"].get<int>();
    auto stress_hold_on_time_ = task_info_js["stress_hold_on_time"].get<int>();
    task_.thread_count = thread_count_;
    task_.stress_hold_on_time = stress_hold_on_time_;

    auto requests_ = task_info_js["requests"];
    if (requests_.find("single") != requests_.end()) {
        auto single_reqs_js = requests_["single"];
        for (auto &&req_it = single_reqs_js.begin(), end = single_reqs_js.end();
             req_it != end; ++req_it) {
            auto key = req_it.key();
            auto value = req_it.value();

            auto method_str = value["method"].get<std::string>();
            request::request_method method_;
            if (method_str == "GET") {
                method_ = request::request_method::GET;
            } else if (method_str == "POST") {
                method_ = request::request_method::POST;
            } else {
                throw std::runtime_error("Not supported request method type!");
            }

            auto url = value["url"].get<std::string>();
            auto body = value["body"].get<std::string>();
            auto headers =
                value["headers"].get<std::map<std::string, std::string>>();
            request tmp_req_{url, method_, body, headers};
            reqs_.single_reqs_[key] = tmp_req_;
        }
    }

    if (requests_.find("multiple") != requests_.end()) {
        // TODO: Add multiple requests parse logic
    }
}

int task_launcher::get_per_thread_sleep_mills(int thread_count_,
                                              int stress_hold_on_time_) {
    if (stress_hold_on_time_ == 0) {
        return 0;
    }

    int per_thread_sleep_time_ =
        (int)(((float)(stress_hold_on_time_ * 1000) / (float)thread_count_));
    return per_thread_sleep_time_;
}

void task_launcher::run_a_request(request& req_value, req_result& req_res) {
    auto url = req_value.url;
    auto method = req_value.req_method;
    auto body = req_value.body;
    auto headers = req_value.headers;

    std::string res{};
    url_parse parse_{url};
    parse_.parse_host_and_path();
    auto host = parse_.get_host();
    auto path = parse_.get_path();

    if(path == "") {
        path = "/";
    }
    
    auto start = std::chrono::system_clock::now();

    bool r_res {false}; 
    if (method == request::request_method::GET) {
        r_res = HttpUtil::get_str(host, path, headers, res);
    } else if(method == request::request_method::POST) {
        r_res = HttpUtil::post_and_get_str(host, path, headers, body, res);
    }
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    req_res.request_time = duration;
    req_res.is_failed = (!r_res);
}


void task_launcher::run() {

    auto thread_count_ = (std::size_t)task_.thread_count;
    auto stress_hold_on_time_ = task_.stress_hold_on_time;
    
    std::cerr << "Stress hold on time: " << stress_hold_on_time_ << std::endl;

    auto sleep_mill_secs =
        get_per_thread_sleep_mills(thread_count_, stress_hold_on_time_);

    std::cerr << "Sleep milliseconds: " << sleep_mill_secs << std::endl;

    std::vector<req_result> req_results;
    for(int i=0; i<thread_count_; ++i) {
        req_results.push_back(req_result{0, false});
    }

    // Handle single requests
    for (auto& req_ : reqs_.single_reqs_) {
        boost::asio::thread_pool pool{thread_count_};
        auto req_name = req_.first;
        auto req_value = req_.second;

        auto start = std::chrono::system_clock::now();

        for (int i = 0; i < thread_count_; ++i) {
            if(sleep_mill_secs > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(sleep_mill_secs));
            }

            boost::asio::post(pool, [this, &req_value, &req_results, i](){
                run_a_request(req_value, req_results[i]);
            });
        }
        pool.join();

        auto end = std::chrono::system_clock::now();

        int min_time{MIN_TIME_BOUND};
        int max_time{MAX_TIME_BOUND};

        int avg_time{0};
        int through_out{0};
        int total_success_count {0};

        for(auto&& req_res: req_results) {
            if(!req_res.is_failed) {
                ++total_success_count;
                if(min_time > req_res.request_time) {
                    min_time = req_res.request_time;
                } 

                if(max_time < req_res.request_time) {
                    max_time = req_res.request_time;
                }
                avg_time += req_res.request_time;
            }
        }
        avg_time = (int)((float)avg_time/(float)total_success_count);
        if(min_time == MIN_TIME_BOUND || max_time == MAX_TIME_BOUND) {
            std::cerr << "All requests failed for request: [" << req_name << "]" << std::endl;
        }

        auto total_time_ = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        through_out = (int)((double)total_success_count/((double)total_time_/(double)1000));
        perf_result p_result{req_value, min_time, max_time, avg_time, through_out};
        results_.single_results_[req_name] = p_result;
    }

    // TODO: Handle multiple requests
    for (auto& multi_req_ : multi_reqs_.multi_reqs_) {
    }
}

// results object to json method
void to_json(json& j, const results& p) {
    json single_res_j{};
    for (auto&& item : p.single_results_) {
        auto request_name = item.first;
        auto perf_value = item.second;
        single_res_j[request_name]["url"] = perf_value.req_.url;
        if (perf_value.req_.req_method == request::request_method::GET) {
            single_res_j[request_name]["method"] = "GET";
        } else if (perf_value.req_.req_method ==
                   request::request_method::POST) {
            single_res_j[request_name]["method"] = "POST";
        }
        single_res_j[request_name]["body"] = perf_value.req_.body;
        single_res_j[request_name]["headers"] = perf_value.req_.headers;

        single_res_j[request_name]["min_request_time"] =
            perf_value.min_request_time;
        single_res_j[request_name]["max_request_time"] =
            perf_value.max_request_time;
        single_res_j[request_name]["avg_request_time"] =
            perf_value.avg_request_time;
        single_res_j[request_name]["through_out"] = perf_value.through_out;
    }
    j["requests"]["single"] = single_res_j;
}

// This one will be used in client task sender.
std::string task_launcher::dump_results() {
    json j = results_;
    return j.dump();
}

void task_launcher::dump_requests() {
    std::stringstream ss;

    if (reqs_.single_reqs_.size() != 0) {
        ss << "Single Requests: " << std::endl;
        for (auto&& request_item : reqs_.single_reqs_) {
            auto req_name = request_item.first;
            auto req_value = request_item.second;
            ss << "Request Name: " << req_name << std::endl;
            ss << "URL: " << req_value.url << std::endl;
            if (req_value.req_method == request::request_method::GET) {
                ss << "Method: "
                   << "GET" << std::endl;
            } else if (req_value.req_method == request::request_method::POST) {
                ss << "Method: "
                   << "POST" << std::endl;
            }

            ss << "Body: " << req_value.body << std::endl;
            ss << "Headers: " << std::endl;
            for (auto&& head_item : req_value.headers) {
                ss << " " << head_item.first << " " << head_item.second
                   << std::endl;
            }

            ss << "Thread Count: " << task_.thread_count << std::endl;
            ss << "Stress hold on time: " << task_.stress_hold_on_time << std::endl; 
        }
    }

    if (multi_reqs_.multi_reqs_.size() != 0) {
        ss << "Multiple Requests: " << std::endl;
        // TODO: Add multiple requests dump logic
    }

    std::cout << ss.str();
}