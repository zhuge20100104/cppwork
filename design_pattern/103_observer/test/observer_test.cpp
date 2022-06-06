#include "observer.hpp"

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

GTEST_TEST(ObserverTests, Observer) {
    Person person {10};
    ConsolePersonObserver cpo;
    person.subscribe(cpo);

    person.set_age(11);
    person.set_age(12);

    // Unsubscribe 之后应该就不接受消息了
    person.unsubscribe(cpo);
    person.set_age(13);
}