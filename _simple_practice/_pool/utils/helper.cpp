#include "utils/helper.h"

#include "glog/logging.h"
#include "http1/http_util.h"

void helper::help(const std::string& path, std::string& res) {
        std::map<std::string, std::string> header {};
        LOG(ERROR) << "path in helper::help: " << path << "\n";
        int i = 0; 
        for(int j=0; j<10; j++) {
            http_util::get_str("cn.bing.com", path, header, res);
        }
}