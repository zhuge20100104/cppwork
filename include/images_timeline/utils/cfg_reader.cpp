#include "cfg_reader.h"

#include <pystring/pystring.h>

#include <fstream>
#include <iostream>


bool parse_line(const std::string& str, std::pair<std::string, std::string>& pair_) {
    auto pos = str.find_first_of(":");
    // 消息中没找到 :
    if(pos == std::string::npos) {
        return false;
    }

    if(pos == 0) {
        return false; 
    }

    auto first_ = str.substr(0, pos);
    auto second_ = str.substr(pos + 1);
    auto first_t_ = pystring::strip(first_);
    auto second_t_ = pystring::strip(second_);
    pair_.first = first_t_;
    pair_.second = second_t_;
    return true;
}


bool cfg_reader::read_file(const std::string& file_name_, std::map<std::string, std::string>& cfg_) {
    std::fstream fs {file_name_};
    if(!fs.is_open()) {
        std::cerr << "open file failed!" << std::endl;
        return false;
    }

    std::string cfg_line;
    while(std::getline(fs, cfg_line)) {
        std::pair<std::string, std::string> pair_{};
        if(parse_line(cfg_line, pair_)) {
            cfg_.insert(std::move(pair_));
        }
    }

    fs.close();
    return true;
}