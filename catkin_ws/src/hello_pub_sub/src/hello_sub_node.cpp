#include <ros/ros.h>
#include <std_msgs/String.h>

void doMsg(std_msgs::String::ConstPtr const& msg_p) {
    ROS_INFO("我听见: %s", msg_p->data.c_str());
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "listener");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe<std_msgs::String>("chatter", 10, doMsg);
    ros::spin();

    return EXIT_SUCCESS;
}