#include "ros/ros.h"

int main(int argc, char* argv[]) {
    // 执行ros节点初始化
    ros::init(argc, argv, "hello_world");
    // 创建ros节点句柄
    ros::NodeHandle n;
    // 控制台输出 hello world
    ROS_INFO("hello world!");

    return EXIT_SUCCESS;
}