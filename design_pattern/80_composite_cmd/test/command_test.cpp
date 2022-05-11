#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "composite_cmd.hpp"
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

GTEST_TEST(CommandTests, Command) {
    BankAccount from;
    BankAccount to;
    
    // 存200
    CompositeBankAccountCommand cbc {{
        BankAccountCommand{from, BankAccountCommand::deposit, 200}
    }};
    cbc.call();

    // 转100到to
    MoneyTransferCommand mtc {
       from,  to, 100
    };
    
    mtc.call();
    
    // 打印结果
    std::cout << from << std::endl;
    std::cout << to << std::endl;
}