#include <glog/logging.h>
#include <gtest/gtest.h>

#include "death_handler/death_handler.h"

#include <vector>
#include <string>
#include <iostream>

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

// 迭代器简单使用
GTEST_TEST(STLIteratorTests, CommonIt) {
    using str_iterator = std::vector<std::string>::iterator;
    std::vector<std::string> names {"john", "jane", "jill", "jack"};
    str_iterator it = names.begin();
    std::cout << "first name is: " << *it << std::endl;
    ASSERT_EQ("john", *it);
}

// 修改迭代器
GTEST_TEST(STLIteratorTests, ModifyIt) {
    using str_iterator = std::vector<std::string>::iterator;
    std::vector<std::string> names {"john", "jane", "jill", "jack"};
    str_iterator it = names.begin();
    ++ it;
    it->append(std::string(" goodall"));
    std::cout << "second name is: " << *it << std::endl;
    
    ASSERT_EQ("jane goodall", *it);
    while(++it != names.end()) {
        std::cout << "another name: " << *it << std::endl;
    }
}

// 反向迭代器
GTEST_TEST(STLIteratorTests, ReverseIt) {
    using str_rev_iterator = std::vector<std::string>::reverse_iterator;
    std::vector<std::string> names {"john", "jane", "jill", "jack"};
    
    for(str_rev_iterator ri = names.rbegin(); ri != names.rend(); ++ri) {
        std::cout << *ri;
        if((ri + 1) != names.rend()) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

// 常量迭代器
GTEST_TEST(STLIteratorTests, ConstIt) {
    using str_const_rev_iterator = std::vector<std::string>::const_reverse_iterator;
    std::vector<std::string> names {"john", "jane", "jill", "jack"};
    str_const_rev_iterator jack = names.crbegin();
    // 不允许更改const_iterator
    // Error: no operator "=" matches these operands
    // *jack = "jack11";
    std::cout << *jack << std::endl;
}

// Range-based for loop 内部也是使用迭代器
GTEST_TEST(STLIteratorTests, RangeBasedFor) {
    using str_const_rev_iterator = std::vector<std::string>::const_reverse_iterator;
    std::vector<std::string> names {"john", "jane", "jill", "jack"};
    // 为避免修改，最好使用右值
    for(auto&& name: names) {
        std::cout << "name = " << name << std::endl;
    }
}

