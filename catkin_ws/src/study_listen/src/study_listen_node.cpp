#include "ros/ros.h"
#include "std_msgs/String.h"

// 创建一个listener的callback调用
void studyCallback(std_msgs::String::ConstPtr const& msg) {
    ROS_INFO("I can see you again, %s", msg->data.c_str());
}

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "study_listener"); // 初始化这么一个node
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("study_topic", 10, studyCallback);
    ros::spin();
    return EXIT_SUCCESS;
}