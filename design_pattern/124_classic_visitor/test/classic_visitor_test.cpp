#include "classic_visitor.hpp"

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

GTEST_TEST(ClassicVisitorTests, ClassicVisitor) {
    // 1+(2-3)
    auto e = std::make_unique<AdditionExpression>(
        std::make_unique<DoubleExpression>(1),
        std::make_unique<SubstractionExpression>(
            std::make_unique<DoubleExpression>(2),
            std::make_unique<DoubleExpression>(3)
        )
    );

    std::ostringstream oss;
    ExpressionPrinter ep;
    ExpressionEvaluator ee;
    ep.visit(e.get());
    ee.visit(e.get());
    std::cout << ep.str() << "=" << ee.result << std::endl;
}