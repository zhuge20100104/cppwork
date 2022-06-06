#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "bank_account.hpp"

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

GTEST_TEST(SmartPointerTests, SmartPointer) {
    BankAccount* a = new CurrentAccount(123);
    a->deposit(321);
    std::cout << *dynamic_cast<CurrentAccount*>(a) << std::endl;
    delete a;

    auto b = std::make_shared<CurrentAccount>(123);
    b->deposit(321);
    std::cout << *b << std::endl;
}