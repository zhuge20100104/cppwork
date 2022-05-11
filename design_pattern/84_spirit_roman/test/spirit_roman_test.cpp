#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "spirit_roman.hpp"
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

GTEST_TEST(SpiritRomanTests, SpiritRoman) {

    namespace qi = boost::spirit::qi;

    using iterator_type = std::string::const_iterator;
    using roman_type = client::roman<iterator_type>;

    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "\t\tRoman Numerals Parser\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "Type a Roman Numeral ...or [q or Q] to quit\n\n";

    // 语法树对象
    roman_type roman_parser;
    std::string str;
    unsigned result{0};
    while(std::getline(std::cin, str)) {
        if(str.empty() || str[0] == 'q' || str[0] == 'Q') {
            break;
        }
        iterator_type iter = str.begin();
        iterator_type end = str.end();
        bool r = qi::parse(iter, end, roman_parser, result);
        if(r && iter == end) {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "result = " << result << "\n";
            std::cout << "-------------------------\n";
        }else {
            std::string rest {iter, end};
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "Stopped at: \"" << rest << "\"\n";
            std::cout << "-------------------------\n";
        }
    }
    std::cout << "Bye...\n\n";
}