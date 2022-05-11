#include "http1/http_util.h"

#include "restclient-cpp/restclient.h"
#include "restclient-cpp/connection.h"

#include <fstream>
#include <sstream>
#include <memory> 
#include <iostream>


std::string get_real_host_name(const std::string& host) {
    std::stringstream host_ss; 
    host_ss << connect_prefix << host;
    return std::move(host_ss.str());
}

bool http_util::get_file(std::string host, std::string path, std::string result_name, const std::map<std::string, std::string>& headers) {
    RestClient::init();
    auto real_host = get_real_host_name(host);
    std::unique_ptr<RestClient::Connection> conn {new RestClient::Connection(real_host)};

    conn->SetTimeout(connect_time_out);
    
    for(auto&& header: headers) {
        conn->AppendHeader(header.first, header.second);
    }

    auto response_ = conn->get(path);
    
    auto body = response_.body;

    RestClient::disable();

    std::ofstream ofs {result_name, std::ios::out | std::ios::binary};

    ofs << body;
    return true;
}   


std::string http_util::get_redirect_url(std::string host, std::string path, const std::map<std::string, std::string>& headers) {
    RestClient::init();
    auto real_host = get_real_host_name(host);
    std::unique_ptr<RestClient::Connection> conn {new RestClient::Connection(real_host)};

    conn->SetTimeout(connect_time_out);
    
    for(auto&& header: headers) {
        conn->AppendHeader(header.first, header.second);
    }

    auto response_ = conn->get(path);
    

     if(response_.headers.find("location") == response_.headers.end()) {
            std::cerr << "Redirect failed" << std::endl;
            RestClient::disable();
            return "";
        }
    auto redirect_url = response_.headers.find("location")->second;
    RestClient::disable();
    return std::move(redirect_url);
}


bool http_util::get_str(std::string host, std::string path, const std::map<std::string, std::string> & headers, std::string &result_string) {
    RestClient::init();
    auto real_host = get_real_host_name(host);
    std::unique_ptr<RestClient::Connection> conn {new RestClient::Connection(real_host)};

    conn->SetTimeout(connect_time_out);
    
    for(auto&& header: headers) {
        conn->AppendHeader(header.first, header.second);
    }

    auto response_ = conn->get(path);
    
    auto body = response_.body;

    RestClient::disable();

    result_string = std::move(body);
    return true;
}

bool http_util::get_zipped_str(std::string host, std::string path, const std::map<std::string, std::string> & headers, std::string &result_string) {
    RestClient::init();
    auto real_host = get_real_host_name(host);
    std::unique_ptr<RestClient::Connection> conn {new RestClient::Connection(real_host)};

    conn->SetTimeout(connect_time_out);
    
    for(auto&& header: headers) {
        conn->AppendHeader(header.first, header.second);
    }

    conn->AppendHeader("Accept-Encoding", "gzip");

    auto response_ = conn->get(path);
    
    auto body = response_.body;

    RestClient::disable();

    result_string = std::move(body);
    return true;
}

bool http_util::post_and_get_str(std::string host, std::string path, const std::map<std::string, std::string> & headers, const std::string& body, std::string &result_string){
    RestClient::init();
    auto real_host = get_real_host_name(host);
    std::unique_ptr<RestClient::Connection> conn {new RestClient::Connection(real_host)};

    conn->SetTimeout(connect_time_out);
    
    for(auto&& header: headers) {
        conn->AppendHeader(header.first, header.second);
    }

    auto response_ = conn->post(path, body);
    
    auto res_body = response_.body;

    RestClient::disable();

    result_string = std::move(res_body);
    return true;
}