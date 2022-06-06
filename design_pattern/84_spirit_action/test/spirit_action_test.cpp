#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "spirit_action.hpp"
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

GTEST_TEST(SpiritActionTests, SpiritAction) {
    using boost::spirit::qi::int_;
    using boost::spirit::qi::parse;
    using client::print;
    using client::writer;
    using client::print_action;

    {
        // example using plain function
        char const* first = "{42}", *last = first + std::strlen(first);
        parse(first, last, '{' >> int_[&print] >> '}');
    }

    {
        // example using simple function object
        char const* first = "{43}", *last = first + std::strlen(first);
        parse(first, last, '{' >> int_[print_action()] >> '}');
    }

    {
        // example using std::bind with a plain function
        char const* first = "{44}", *last = first + std::strlen(first);
        parse(first, last, '{' >> int_[std::bind(print, std::placeholders::_1)] >> '}');
    }

    {
        // example using std::bind with a member function
        char const* first = "{45}", *last = first + std::strlen(first);
        writer w;
        parse(first, last, '{' >> int_[std::bind(&writer::print, &w,std::placeholders::_1)] >> '}');
    }

    {
        // example using lambda
        char const* first = "{46}", *last = first + std::strlen(first);
        auto print_func = [](auto const& ele) {
            std::cout << ele << std::endl;
        };
        parse(first, last, '{' >> int_[print_func] >> '}');
    }
}