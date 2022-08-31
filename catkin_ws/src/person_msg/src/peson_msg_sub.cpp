#include <ros/ros.h>
#include "person_msg/Person.h"

void doPerson(person_msg::PersonConstPtr const& person_p) {
    ROS_INFO("订阅的个人信息: 姓名: %s, 年龄: %d, 身高: %.2f", person_p->name.c_str(), person_p->age, person_p->height);
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "person_listener");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<person_msg::Person>("/person", 10, doPerson);
    ros::spin();
    return EXIT_SUCCESS;
}