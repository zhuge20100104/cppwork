#ifndef _HTTP_UTIL_H_
#define _HTTP_UTIL_H_

#define CPPHTTPLIB_OPENSSL_SUPPORT
#define CPPHTTPLIB_ZLIB_SUPPORT

#include "http/httplib.h"
#include <string>

const int ConnectionTimeout = 120;
const int ReadTimeout = 120;

class HttpUtil {
    public:
        /**
         * HttpUtil get method
         * 
         * @param: url the url to be used to get a web page from remote server
         * @param: path the path to be used to get a web page from remote server
         * @param: result_name the download result file path
         */
        static bool get(std::string url, std::string path, std::string result_name);

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