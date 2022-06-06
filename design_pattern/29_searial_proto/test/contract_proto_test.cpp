#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "serial_proto_fact.hpp"

#include <utility>
#include <gtest/gtest.h>
#include "df/df.h"


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

GTEST_TEST(ContractProtoTests, ContractProto) {
    Contract john;
    john.name = "John Doe";
    john.address = std::make_unique<Address>("123 East Dr", "London", 123);

    auto jane = clone_(john);
    jane.name = "Jane Done";
    jane.address->street = "123B West Dr";
    jane.address->suite = 300;

    std::cout << john << "\n" << jane << "\n"; 
}