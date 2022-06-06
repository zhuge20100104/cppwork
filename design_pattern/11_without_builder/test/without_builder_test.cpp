#include "death_handler/death_handler.h"
#include "json/json.hpp"
#include <glog/logging.h>
#include <gtest/gtest.h>
#include "df/df.h"

#include <string>
#include <sstream>

using json = nlohmann::json;

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

GTEST_TEST(WithoutBuilderTests, WithoutBuilder) {
    auto text = "hello";
    std::string output;
    output += "<p>";
    output += text;
    output += "</p>";

    std::cout << output << "\n";

    std::string words[] = {"hello", "world"};
    std::ostringstream oss;
    oss << "<ul>";
    for(auto&& w: words) {
        oss << "<li>" << w << "</li>";
    }
    oss << "</ul>";
    std::cout << oss.str() << "\n";
}