#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "func_decorator.hpp"

#include <utility>
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

double add(double a, double b) {
    std::cout << a << " + " << b << " = " << (a+b) << std::endl;
    return a+b;
}

GTEST_TEST(FuncDecoratorTests, FuncDecorator) {
    // 简单的hello 函数，无参数，无返回
    Logger([](){
        std::cout << "Hello" << std::endl;
    }, "HelloFunction")();

    // 调用辅助函数构造 logger2对象
    auto log2 = make_logger2([]() {
        std::cout << "Hello" << std::endl;
    }, "HelloFunction");

    log2();

    // 带参数和返回值的装饰器
    auto log_add = make_logger3(add, "Add");
    auto result = log_add(2, 3);
    std::cout << "result = " << result << "\n";
}