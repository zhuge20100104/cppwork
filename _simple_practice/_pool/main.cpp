#include <boost/asio.hpp>
#include <glog/logging.h>
#include <boost/bind/bind.hpp>

#include "death_handler/death_handler.h"
#include "glog/logging.h"
#include "utils/helper.h"

#include <string>
#include <chrono>
#include <thread>

int main(int argc, char* argv[]) {

    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 2;

    Debug::DeathHandler dh;

    google::InitGoogleLogging("./logs.log");

    boost::asio::thread_pool pool {10};
    std::vector<std::string> results;
    for(int i=0;i<10; ++i) { 
        results.emplace_back("");
    }
    std::string hello = "hello";
    std::string path = "/";
    for(int i=0;i<10; ++i) {
        boost::asio::post(pool, boost::bind(&helper::help, std::cref(path), std::ref(results[i])));
    }
    
    pool.join();

    for(auto&& res: results) {
        LOG(ERROR) << res << "\n";
    }
    return EXIT_SUCCESS;
}