#include "ros/ros.h"
#include "study_msgs/StudyMsg.h"

void studyCustomCallback(study_msgs::StudyMsg::ConstPtr const& msg) {
    ROS_INFO("I think I can't forget you, %s, %d", msg->detail.c_str(), msg->id);
}

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "study_custom_listener");
    ros::NodeHandle n;
    ros::Subscriber sub_new = n.subscribe<study_msgs::StudyMsg>("/study_custom", 10, studyCustomCallback);
    ros::spin();
    return EXIT_SUCCESS;
}