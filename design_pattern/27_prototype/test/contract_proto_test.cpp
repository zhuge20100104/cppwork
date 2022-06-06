#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "contract_proto.hpp"

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
    Contract john {"John Doe", std::make_unique<Address>("123 East Dr", "London", 123)};
    Contract jane = john;  // 拷贝构造函数深拷贝
    jane.name = "Jane Smith";
    jane.address->suite = 103;
    std::cout << john << "\n";
    std::cout << jane << "\n";
}