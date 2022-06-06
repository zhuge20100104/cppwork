#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "di/di.hpp"
#include "singleton_di.hpp"

#include <utility>
#include <gtest/gtest.h>
#include "df/df.h"

namespace di = boost::di;


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

GTEST_TEST(SingletonDITests, SingletonDI) {
    auto injector = di::make_injector(
        di::bind<Foo>().to<Foo>().in(di::singleton)
    );

    auto bar1 = injector.create<std::shared_ptr<Bar<Foo>>>();
    auto bar2 = injector.create<std::shared_ptr<Bar<Foo>>>();
    EXPECT_EQ(bar1->foo->name(), bar2->foo->name());
    EXPECT_EQ(bar1->foo.get(), bar2->foo.get());
}