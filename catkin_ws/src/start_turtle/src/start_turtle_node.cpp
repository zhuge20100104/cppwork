#include "ros/ros.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "start_turtle");
    ROS_INFO("启动小乌龟程序");
    return EXIT_SUCCESS;
}