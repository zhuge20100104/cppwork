#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "spirit_sum.hpp"
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

GTEST_TEST(SpiritSumTests, SpiritSum) {
    std::cout << "////////////////////////////////////////\n\n";
    std::cout << "A sum parser for spirit\n\n";
    std::cout << "////////////////////////////////////////\n\n";

    std::cout << "Give me a comma separated list of numbers\n";
    std::cout << "The numbers are added using Phoenix\n";
    std::cout << "Type [q or Q] to quit\n\n";

    std::string str;
    while(std::getline(std::cin, str)) {
        if(str.empty() || str[0] == 'q' || str[0] == 'Q') {
            break;
        }
        double n{0.0};
        if(client::adder(str.begin(), str.end(), n)) {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << str << " parse OK: " << std::endl;
            std::cout << "sum = " << n << "\n";
            std::cout << "-------------------------\n";
        }else {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }
    }
    std::cout << "Bye...\n\n";
}