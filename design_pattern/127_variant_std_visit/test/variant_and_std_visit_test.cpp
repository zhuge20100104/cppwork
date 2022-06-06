#include "variant_and_std_visit.hpp"

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <algorithm>

#include "death_handler/death_handler.h"

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

GTEST_TEST(StdVisitTests, StdVisit) {
    std::variant<std::string, int> house;
    house = 221;
    AddressPrinter ap;
    std::visit(ap, house);

    // 2: create a std::visitor in-place
    std::visit([](auto& arg){
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "A house called " << arg << "\n";
        } else {
            std::cout << "House number: " << arg << "\n";
        }
    }, house);
}