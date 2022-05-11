#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "pingpong_svc.hpp"

#include "http/http_util.h"
#include <utility>
#include <gtest/gtest.h>



int main(int argc, char** argv) {
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;

    Debug::DeathHandler dh;

    google::InitGoogleLogging("./logs.log");
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

GTEST_TEST(PingPongSvcTests, PingPongSvc) {
    PingServer::run();
}

GTEST_TEST(PingPongSvcTests, PingPongClient) {
    std::string host {"127.0.0.1"};
    std::string path {"/api/pingpong/hello"};
    std::string res_str;
    httplib::Client cli(host, 80);
    auto res = cli.Get(path.c_str());
    if(httplib::Error::Success != res.error()) {
        ASSERT_TRUE(false);
    }
    std::cout << res->body << "\n";
    ASSERT_EQ("hello pong", res->body);
}