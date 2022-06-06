#include "http/http_util.h"

#include <iostream>
#include <fstream>


bool HttpUtil::get(std::string url, std::string path, std::string result_name) {

    try {
        httplib::Client cli {url};
        cli.set_connection_timeout(ConnectionTimeout);

        auto res = cli.Get(path.c_str());
        if(res->status != 200) {
            std::cerr << "Get [" << url << path << "] failed" << std::endl;
            std::cerr << "Status code : [" << res->status << "]" << "\n"   << "Result body : [" << res->body << "]" 
            << std::endl; 
            cli.stop();
            return false;
        }
        std::ofstream os {result_name, std::ios_base::out | std::ios_base::binary};
        os << res->body;
        cli.stop();
        return true;
    } catch(const std::exception & e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return false;
    }
}


std::string HttpUtil::get_redirect_url(std::string host, std::string path, const std::map<std::string, std::string>& headers) {
    try {

        #ifdef CPPHTTPLIB_OPENSSL_SUPPORT
            auto port = 443;
            httplib::SSLClient cli(host, port);
        #else
            auto port = 80;
            httplib::Client cli(host, port);
        #endif

        cli.set_connection_timeout(ConnectionTimeout);
        cli.set_read_timeout(ReadTimeout);
        cli.set_follow_location(false);

        httplib::Headers headers_ {};
        for(auto&& item: headers) {
            headers_.insert(item);
        }

        auto res = cli.Get(path.c_str(), headers_);

        if(res->headers.find("location") == res->headers.end()) {
            std::cerr << "Redirect failed" << std::endl;
            cli.stop();
            return "";
        }
        auto redirect_url = res->headers.find("location")->second;
        cli.stop();
        return std::move(redirect_url);
    } catch(const std::exception & e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return "";
    }
}

bool HttpUtil::get_file(std::string host, std::string path, std::string result_name, const std::map<std::string, std::string>& headers) {

    try {

        #ifdef CPPHTTPLIB_OPENSSL_SUPPORT
            auto port = 443;
            httplib::SSLClient cli(host, port);
        #else
            auto port = 80;
            httplib::Client cli(host, port);
        #endif

        cli.set_connection_timeout(ConnectionTimeout);
        cli.set_read_timeout(ReadTimeout);


        httplib::Headers headers_ {};
        for(auto&& item: headers) {
            headers_.insert(item);
        }

        std::ofstream os {result_name};

        auto res = cli.Get(path.c_str(), headers_,
              [&](const char *data, size_t data_length) {
                os << std::string(data, data_length);
                return true;
              });

        if(!res || res->status != 200) {
            cli.stop();
            return false;
        }
        cli.stop();
        return true;
    } catch(const std::exception & e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return false;
    }
}

bool HttpUtil::get_str(std::string host, std::string path, const std::map<std::string, std::string> & headers, std::string &result_string) {
     try {
        #ifdef CPPHTTPLIB_OPENSSL_SUPPORT
            auto port = 443;
            httplib::SSLClient cli(host, port);
        #else
            auto port = 80;
            httplib::Client cli(host, port);
        #endif

        cli.set_connection_timeout(ConnectionTimeout);
        cli.set_read_timeout(ReadTimeout);

        httplib::Headers headers_ {};
        for(auto&& item: headers) {
            headers_.insert(item);
        }
        
        auto res = cli.Get(path.c_str(), headers_);
        
        if(res == nullptr) {
            cli.stop();
            return false;
        }

        if(res->status != 200)  {
            // Print out failed request id for debug
            if(res->headers.find("AA-Request-ID") != res->headers.end()) {
                auto req_id = res->headers.find("AA-Request-ID")->second;
                std::cerr << "None 200 response Request ID: " << req_id << "\n";
            }
        }

        result_string = res->body;
        cli.stop();
        return true;
    } catch(const std::exception & e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return false;
    }
}

bool HttpUtil::get_zipped_str(std::string host, std::string path, const std::map<std::string, std::string> & headers, std::string &result_string) {
    try {
        
        #ifdef CPPHTTPLIB_OPENSSL_SUPPORT
            auto port = 443;
            httplib::SSLClient cli(host, port);
        #else
            auto port = 80;
            httplib::Client cli(host, port);
        #endif
        cli.set_decompress(false);
        cli.set_connection_timeout(ConnectionTimeout);
        cli.set_read_timeout(ReadTimeout);

        httplib::Headers headers_ {};
        for(auto&& item: headers) {
            headers_.insert(item);
        }
        headers_.insert({"Accept-Encoding", "gzip, deflate"});
        
        auto res = cli.Get(path.c_str(), headers_);
        
        if(res == nullptr) {
            cli.stop();
            return false;
        }

        result_string = res->body;
        cli.stop();
        return true;
    } catch(const std::exception & e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return false;
    }
}

bool HttpUtil::post_and_get_str(std::string host, std::string path, const std::map<std::string, std::string> & headers, const std::string& body, std::string &result_string){
    try {
        #ifdef CPPHTTPLIB_OPENSSL_SUPPORT
            auto port = 443;
            httplib::SSLClient cli(host, port);
        #else
            auto port = 80;
            httplib::Client cli(host, port);
        #endif

        cli.set_connection_timeout(ConnectionTimeout);
        cli.set_read_timeout(ReadTimeout);

        httplib::Headers headers_ {};
        for(auto&& item: headers) {
            headers_.insert(item);
        }
        auto res = cli.Post(path.c_str(), headers_, body.c_str(), body.size(), "application/json");
        
        if(res == nullptr) {
            cli.stop();
            return false;
        }

        result_string = res->body;
        cli.stop();

        return true;
    } catch(const std::exception & e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return false;
    }
}