#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "spirit_emp_struct.hpp"
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

GTEST_TEST(SpiritEmpStructTests, SpiritEmpStruct) {
   
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "\t\tAn employee parser for Spirit...\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";

    std::cout
        << "Give me an employee of the form :"
        << "employee{age, \"surname\", \"forename\", salary } \n";
    std::cout << "Type [q or Q] to quit\n\n";

    namespace qi = boost::spirit::qi;
    using boost::spirit::ascii::space;
    using iterator_type = std::string::const_iterator;
    using employee_parser = client::employee_parser<iterator_type>;

    std::string str;
    employee_parser g;
  
    while(std::getline(std::cin, str)) {
        if(str.empty() || 'q' == str[0]  || 'Q' == str[0]) {
            break;
        }

        client::employee emp;
        iterator_type iter = str.begin();
        iterator_type end = str.end();

        bool r = qi::phrase_parse(iter, end, g, space, emp);
        if(r && iter == end) {
            std::cout << boost::fusion::tuple_open('[');
            std::cout << boost::fusion::tuple_close(']');
            std::cout << boost::fusion::tuple_delimiter(", ");

            std::cout << "------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << boost::fusion::as_vector(emp) << std::endl;
            std::cout << "------------------------\n";
        } else {
            std::cout << "------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "------------------------\n";
        }
    }
    std::cout << "Bye...\n\n";
}