#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

// 编写一个node并发布出来
int main(int argc, char* argv[]) {
    ros::init(argc, argv, "study_talker");
    ros::NodeHandle n; // ros提供的一个类，可以实例化publisher，进行发布数据

    // 定义node要发布的topic 名称,以及发布的有效率（表示10为有效的，如果很久都没有缓存进去，那么早期发布的就会被释放掉）
    ros::Publisher study_pub = n.advertise<std_msgs::String>("/study_topic", 10);
    ros::Rate loop_rate(10); // 每秒发布10次
    // 记录发布的次数
    int count = 0;
    while(ros::ok()) {
        // ros::ok的作用是，只要ros master正常运行，如果没有中断操作，都会继续运行的
        std_msgs::String msg; // 定义要发布到ros里的变量名称，或者实例化一个对象来保存要发布的消息
        std::stringstream ss;
        ss << "Hello study world!" << count;
        ++count;
        msg.data = ss.str(); // 发布的字符串封装到ros变量
        study_pub.publish(msg); // 把消息通过ros上面定义的publisher发布出去
        loop_rate.sleep(); // 暂停 0.1秒
    }
}