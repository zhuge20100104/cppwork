#ifndef _FREDRIC_PINGPONG_SVC_HPP_
#define _FREDRIC_PINGPONG_SVC_HPP_

#include "http/httplib.h"
#include "pystring/pystring.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

struct PingServer {
    static void run() {
        httplib::Server svr;
        svr.Get(R"(/api/pingpong/(.*))", [](httplib::Request const& req, httplib::Response& res){
            std::stringstream res_ss;
            auto path = req.path;
            std::vector<std::string> res_vec;
            pystring::split(path, res_vec, "/");
            auto msg = *res_vec.rbegin();
            res_ss << msg << " pong";
            res.set_content(res_ss.str(), "text/plain");
        });

        svr.listen("0.0.0.0", 80);
    }
};
#endif