#include "tasks/task_reader.h"
#include "json/json.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

using json = nlohmann::json;


task_reader::task_reader(task t_): task_(t_) {
}

std::string task_reader::parse_tasks(const std::string& task_file_path) {
    std::fstream fs(task_file_path);
    if(!fs.is_open()) {
        std::cerr << "Open file [" << task_file_path << "] failed" << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << fs.rdbuf();
    std::string cases_str = buffer.str();
    auto case_js = json::parse(cases_str);
    case_js["thread_count"] = task_.thread_count;
    case_js["stress_hold_on_time"] = task_.stress_hold_on_time;
    return std::move(case_js.dump());
}

