#include "ros/ros.h"

#include "study_msgs/StudyMsg.h"
void studyCallbackParam(study_msgs::StudyMsg::ConstPtr const& msg) {
    ROS_INFO("I think I can forget you, %s, %d", msg->detail.c_str(), msg->id);
}

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "study_param_listener");
    ros::NodeHandle n;
    ros::Subscriber sub_param = n.subscribe<study_msgs::StudyMsg>("/params_topic", 10, studyCallbackParam);
    ros::spin();
    return 0;
}