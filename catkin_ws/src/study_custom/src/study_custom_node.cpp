#include "ros/ros.h"
#include <sstream>
#include "study_msgs/StudyMsg.h"

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "study_custom");
    ros::NodeHandle n;
    ros::Publisher study_pub = n.advertise<study_msgs::StudyMsg>("/study_custom", 10);
    ros::Rate loop_rate(10); // 10 per/s

    int count = 0;
    while(ros::ok()) {
        // 发布自定义消息类型
        study_msgs::StudyMsg studyMsg;
        studyMsg.id = count;
        studyMsg.detail = "Hello study world! new";
        ++ count;
        study_pub.publish(studyMsg);
        loop_rate.sleep();
    }
}