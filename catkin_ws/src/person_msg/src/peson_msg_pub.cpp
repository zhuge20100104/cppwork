#include <ros/ros.h>
#include "person_msg/Person.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
    // 初始化ros节点
    ros::init(argc, argv, "person_talker");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<person_msg::Person>("/person", 1000);
    
    // 第一条消息发送时，publisher还未在roscore中注册完毕，
    // 先等一会再发
    ros::Duration(3.0).sleep();

    person_msg::Person p;
    p.name = "祝中良";
    p.age = 35;
    p.height = 1.72;
    ros::Rate r(1);

    while(ros::ok()) {
        pub.publish(p);
        p.age += 1;
        if(p.age > 40) {
            p.age = 35;
        }
        ROS_INFO("我叫%s, 今年%d岁, 高%.2f米", p.name.c_str(), p.age, p.height);
        r.sleep();
        ros::spinOnce();
    }
    return EXIT_SUCCESS;
}