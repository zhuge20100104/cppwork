#include "boost_iterator_facade.hpp"

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

// 单链表前向遍历迭代器
GTEST_TEST(BinaryTreeIteratorTests, BinaryTreeIt) {
    Node alpha {"alpha"};
    Node beta {"beta", &alpha};
    Node gamma {"gamma", &beta};

    std::for_each(ListIterator{&alpha}, ListIterator{}, [](auto const& ele) {
        std::cout << ele.value << std::endl;
    });
}
