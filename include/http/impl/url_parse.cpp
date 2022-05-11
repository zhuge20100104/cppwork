#include "http/url_parse.h"

url_parse::url_parse(const std::string& url): url_(url) {
}

void url_parse::parse_host_and_path() {
    auto host_index = this->url_.find("://");
    host_index = host_index + 3;
    auto host_and_path_str = this->url_.substr(host_index);
    auto host_end_index = host_and_path_str.find_first_of('/');
    if(host_end_index == std::string::npos) {
        host_ =  host_and_path_str;
        path_ = "";
        return;
    }

    host_ = host_and_path_str.substr(0, host_end_index);
    path_ = host_and_path_str.substr(host_end_index);
}

std::string url_parse::get_host() const {
    return host_;
}
std::string url_parse::get_path() const {
    return path_;
}

