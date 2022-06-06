#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "rect_draw_cache.hpp"

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

GTEST_TEST(MultitonTests, Multiton) {
    DrawableObjects objs {
        std::make_shared<VectorRectangle>(10,10,100,100),
        std::make_shared<VectorRectangle>(30,30,60,60)
    };
    Drawer<LineToPointCacheAdapter> d{objs};
    d.draw();
    d.wait_to_dispose();
}