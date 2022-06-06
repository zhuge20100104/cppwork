#ifndef _FREDRIC_URL1_PARSE_H_
#define _FREDRIC_URL1_PARSE_H_

#include <string>

// URL 解析器，将URL解析成host和path两个部分
struct url_parse {
    url_parse(const std::string& url);
    
    void parse_host_and_path();

    std::string get_host() const;
    std::string get_path() const;

    private:
        std::string url_;
        std::string host_;
        std::string path_;
};
#endif