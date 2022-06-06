#include "observer_safely.hpp"


#include <glog/logging.h>
#include <gtest/gtest.h>

#include <fstream>
#include <memory>
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

// Safe Observer
GTEST_TEST(SafeObserverTests, SafeObserver) {
    Person p{0};
    TrafficAdministration ta;
    p.subscribe(ta);

    p.set_age(15);
    p.set_age(16);
    try {
        p.set_age(17); //尝试触发死锁 
    }catch(std::exception const& ex) {
        std::cout << "Oops, " << ex.what() << "\n";
    }
}   