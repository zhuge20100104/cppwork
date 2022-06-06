#ifndef _FREDRIC_REQUEST_H_
#define _FREDRIC_REQUEST_H_
#include "json/json.hpp"

#include <map>
#include <string>
#include <vector>

using json = nlohmann::json;

struct request {
    enum request_method { GET, POST };

    std::string url;
    request_method req_method{GET};
    std::string body;
    std::map<std::string, std::string> headers{};
};

struct req_result {
    int request_time{0};
    bool is_failed{false};
};

struct perf_result {
    request req_;
    int min_request_time;  // 最小响应时间
    int max_request_time;  // 最大响应时间
    int avg_request_time;  // 平均响应时间
    int through_out;       // 吞吐量
};

// TODO: struct multi_perf_result

struct requests {
    std::map<std::string, request> single_reqs_{};
};

struct results {
    std::map<std::string, perf_result> single_results_{};
};

struct multi_requests {
    std::map<std::string, std::vector<request>> multi_reqs_{};
};

// TODO: struct multi_results

#endif