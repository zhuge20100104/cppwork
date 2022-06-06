#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "spirit_complex.hpp"
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

GTEST_TEST(SpiritComplexTests, SpiritComplex) {
    std::cout << "////////////////////////////////////////\n\n";
    std::cout << "A complex number micro parser for spirit\n\n";
    std::cout << "////////////////////////////////////////\n\n";

    std::cout << "Give me a complex number of the form r or (r) or (r,i) \n";
    std::cout << "Type [q or Q] to quit\n\n";

    std::string str;
    while(std::getline(std::cin, str)) {
        if(str.empty() || str[0] == 'q' || str[0] == 'Q') {
            break;
        }
        std::complex<double> c;
        if(client::parse_complex(str.begin(), str.end(), c)) {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "Got: " << c << std::endl;
            std::cout << "-------------------------\n";
        }else {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }
    }
    std::cout << "Bye...\n\n";
}