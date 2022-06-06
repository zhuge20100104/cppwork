#include "api_accuracy/utils/io_util.h"

#include <glog/logging.h>
#include <fstream>

std::string IOUtil::read_file(const std::string& file_name)  {
        std::fstream fs{file_name};
        if(!fs.is_open()) {
            LOG(ERROR) << "Open file [" << file_name << "] failed" << "\n";
            return "";
        }
        std::stringstream ss {};
        ss << fs.rdbuf();
        return std::move(ss.str());
}

bool IOUtil::write_file(const std::string& file_name, const std::string& content) {
    std::fstream fs{file_name, std::ios::out | std::ios::trunc};
    if(!fs.is_open()) {
        LOG(ERROR) << "Open file [" << file_name << "] failed" << "\n";
        return false;
    }

    fs << content;
    fs.close();
    return true;
}