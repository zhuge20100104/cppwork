#ifndef _FREDRIC_COMMUNICATION_PROXY_HPP_
#define _FREDRIC_COMMUNICATION_PROXY_HPP_

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <concepts>
#include <utility>
#include "http/httplib.h"

template <typename T>
concept PingableType = requires(T value) {
    {value.ping(std::declval<std::string const&>())} -> std::convertible_to<std::string>;
};

struct Pong {
    std::string ping(std::string const& message) const {
        return message + " pong";
    }
};

struct RemotePong {
    std::string ping(std::string const& message) const {
        std::string host {"127.0.0.1"};
        std::stringstream ss_path;
        ss_path << "/api/pingpong/";
        ss_path << message;
        std::string path {ss_path.str()};
        std::string res_str;
        httplib::Client cli(host, 80);
        auto res = cli.Get(path.c_str());
        if(httplib::Error::Success != res.error()) {
            std::cout << "request failed\n";
            return ""; 
        }
        return res->body;
    }
};

template <PingableType PingableT> 
void try_it(PingableT const& pp) {
    std::cout << pp.ping("hello") << "\n";
}

#endif