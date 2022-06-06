#include "binary_tree_iterator.hpp"

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <fstream>
#include <memory>

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

// 中根遍历迭代器
GTEST_TEST(BinaryTreeIteratorTests, BinaryTreeIt) {
    BinaryTree<std::string> family (
        new Node<std::string>("me",
        new Node<std::string>("mother",
            new Node<std::string>("Mother's mother"),
            new Node<std::string>("Mother's father")
        ),
        new Node<std::string>("father"))
    );

    for(auto it = family.begin(); it!=family.end(); ++it) {
        std::cout << (*it).value << "\n";
    }
}
