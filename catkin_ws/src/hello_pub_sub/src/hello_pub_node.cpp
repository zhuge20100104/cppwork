#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "talker");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<std_msgs::String>("chatter", 10);
    // 第一条消息发送时，publisher还未在roscore中注册完毕，
    // 先等一会再发
    ros::Duration(3.0).sleep();

    std_msgs::String msg;

    std::string msg_front = "hello 你好! ";
    int count = 0;
    // 1秒1次
    ros::Rate r(1);

    while(ros::ok()) {
        std::stringstream ss;
        ss << msg_front << count;
        msg.data = ss.str();
        pub.publish(msg);
        ROS_INFO("发送的消息: %s", msg.data.c_str());
        r.sleep();

        ++count;
        ros::spinOnce();
    }
    return EXIT_SUCCESS;
}