#include <ros/ros.h>
#include "svr_server_client/AddInts.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
    
    ROS_INFO("Args count: %d", argc);
    ROS_INFO("args 0: %s", argv[0]);
    ROS_INFO("args 1: %s", argv[1]);
    ROS_INFO("args 2: %s", argv[2]);
    ROS_INFO("args 3: %s", argv[3]);
    ROS_INFO("args 4: %s", argv[4]);

    if(argc!=5) {
        ROS_ERROR("请提交两个整数");
        return EXIT_FAILURE;
    }

    ros::init(argc, argv, "AddInts_Client");
    ros::NodeHandle nh;
    auto client = nh.serviceClient<svr_server_client::AddInts>("add_ints");
    // 等待服务端ready再请求
    client.waitForExistence();

    svr_server_client::AddInts ai;
    ai.request.num1 = std::atoi(argv[1]);
    ai.request.num2 = std::atoi(argv[2]);

    auto flag = client.call(ai);

    if(flag) {
        ROS_INFO("请求正常处理，响应结果: %d", ai.response.sum);
    }else {
        ROS_ERROR("请求处理失败...");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
