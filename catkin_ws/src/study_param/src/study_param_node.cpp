#include "ros/ros.h"
#include "study_msgs/StudyMsg.h"

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "study_param");
    ros::NodeHandle n;
    ros::Publisher study_pub_param = n.advertise<study_msgs::StudyMsg>("/params_topic", 10);

    ros::Rate loop_rate(10); // 10per/s
    int count = 0;
    while(ros::ok()) {
        // 测试参数中心
        study_msgs::StudyMsg studyMsg_param;
        std::string param_string;
        n.param<std::string>("myparam", param_string, "cc");
        studyMsg_param.detail = param_string;
        studyMsg_param.id = count;
        ++count;

        study_pub_param.publish(studyMsg_param);
        loop_rate.sleep();
    }
}