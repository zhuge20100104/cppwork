#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "geo_shapes.hpp"
#include "geo_shapes_virtual.hpp"

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

// 静态多态实现组合模式
GTEST_TEST(GeoShapesTests, GeoShapes) {
    Circle c1, c2;

    Group<Circle> root {"root"};
    root.objects.push_back(c1);

    Group<Circle> subgroup {"sub"};
    subgroup.objects.push_back(c2);
    
    Group<Group<Circle>> groups{"groups"};
    groups.objects.push_back(root);
    groups.objects.push_back(subgroup);
    groups.draw();
}

// 动态多态实现组合模式
GTEST_TEST(GeoShapesTests, GeoShapesVirtual) {
    GroupV root {"root"};
    CircleV c1, c2;

    root.objects.push_back(&c1);

    GroupV subgroup {"sub"};
    subgroup.objects.push_back(&c2);
    root.objects.push_back(&subgroup);
    root.draw();
}