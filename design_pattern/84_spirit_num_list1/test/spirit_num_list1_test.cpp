#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "spirit_num_list1.hpp"
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

GTEST_TEST(SpiritNumList1Tests, SpiritNumList1) {
    std::cout << "\t\tComma separated list parser for Spirit\n\n";
    std::cout << "Give me a comma separated list of numbers.\n";
    std::cout << "Type [q or Q] to quit\n\n";

    std::string str;
    while(std::getline(std::cin, str)) {
        if(str.empty() || 'q' == str[0]  || 'Q' == str[0]) {
            break;
        }

        if(client::parse_numbers(str.begin(), str.end())) {
            std::cout << "------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << str << " parses OK" << std::endl;                
        } else {
            std::cout << "------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "------------------------\n";
        }
    }
    std::cout << "Bye...\n\n";
}