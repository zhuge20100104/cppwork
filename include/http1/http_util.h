#ifndef _HTTP1_UTIL_H_
#define _HTTP1_UTIL_H_

#include <string>
#include <map>

const int connect_time_out = 2000;
const std::string connect_prefix = "https://";

class http_util {
    public:

         /**
         * HttpUtil get_file method
         * 
         * @param: host the host to be used to get an item from remote server
         * @param: path the path to be used to get an item from remote server
         * @param: result_name the download result file path
         */
        static bool get_file(std::string host, std::string path, std::string result_name, const std::map<std::string, std::string>& headers={});

        static std::string get_redirect_url(std::string host, std::string path, const std::map<std::string, std::string>& headers={});

        static bool get_str(std::string host, std::string path, const std::map<std::string, std::string> & headers, std::string &result_string);


        static bool get_zipped_str(std::string host, std::string path, const std::map<std::string, std::string> & headers, std::string &result_string);

        static bool post_and_get_str(std::string host, std::string path, const std::map<std::string, std::string> & headers, const std::string& body,std::string &result_string);
};
#endif