#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "commu_proxy.hpp"

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

GTEST_TEST(CommuProxyTests, CommuProxyPong) {
   Pong pp;
   for(int i=0; i<3; ++i) {
       try_it(pp);
   }
}

GTEST_TEST(CommuProxyTests, CommuProxyRemotePong) {
    RemotePong pp;
    for(int i=0; i<3; ++i) {
        try_it(pp);
    }
}