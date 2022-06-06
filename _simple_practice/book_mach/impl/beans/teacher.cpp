#include "beans/teacher.h"
#include "beans/order_file.h"
#include "utils/func.h"

#include <iostream>
#include <sstream>
#include <vector>

teacher::teacher() {

}

teacher::teacher(int emp_id, std::string name, std::string pwd) {
    m_emp_id = emp_id;
    m_name = name;
    m_pwd = pwd;
}

void teacher::oper_menu() {
    std::cout << "欢迎教师: " << m_name << "登录!" << std::endl;
    std::cout << "\t\t---------------------------------------------\n";
    std::cout << "\t\t|                                            |\n";
    std::cout << "\t\t|               1.查看所有预约                 |\n";
    std::cout << "\t\t|                                            |\n";
    std::cout << "\t\t|               2.审核预约                    |\n";
    std::cout << "\t\t|                                            |\n";
    std::cout << "\t\t|               0.注销登录                    |\n";
    std::cout << "\t\t|                                            |\n";
    std::cout << "\t\t---------------------------------------------\n";
    std::cout << "请选择您的操作: " << std::endl;
}

// 查看所有预约
void teacher::show_all_order() {
    order_file of;
    if(of.m_size == 0) {
        std::cout << "无预约记录" << std::endl;
        Funcs::pause();
        Funcs::clear();
        return;
    }

    for(int i=0; i<of.m_size; ++i) {
        std::cout << (i+1) << ".";
        std::cout << "预约日期: 周" << of.m_order_data[i]["date"];
        std::cout << " 时段: " << (of.m_order_data[i]["interval"] == "1" ? "上午": "下午");
        std::cout << " 学号: " << (of.m_order_data[i]["stu_id"]);
        std::cout << " 姓名: " << (of.m_order_data[i]["stu_name"]);
        std::cout << " 机房: " << (of.m_order_data[i]["room_id"]);

        std::stringstream status_ss;
        status_ss << " 状态: "; // 0 取消预约 1 审核中 2 已预约 -1 预约失败
        if(of.m_order_data[i]["status"] == "1") {
            status_ss << "审核中";
        } else if(of.m_order_data[i]["status"] == "2") {
            status_ss << "预约成功";
        } else if(of.m_order_data[i]["status"] == "-1") {
            status_ss << "审核未通过，预约失败";
        } else {
            status_ss << "预约已取消";
        }

        std::cout << status_ss.str() << std::endl;
    }

    Funcs::pause();
    Funcs::clear();
}

// 审核预约
void teacher::valid_order() {
    order_file of;
    if(of.m_size == 0) {
        std::cout << "无预约记录" << std::endl;
        Funcs::pause();
        Funcs::clear();
        return;
    }

    std::cout << "待审核的预约记录如下:" << std::endl;

    // 所有能被取消的记录索引
    std::vector<int> v;
    int index = 1;

    for(int i=0; i<of.m_size; ++i) {
        // 不管是哪个学生的订单，都可以审核，只能审核 审核中的订单
        if(of.m_order_data[i]["status"] == "1") {
            v.push_back(i);
            std::cout << index ++ << "."; 
            std::cout << "预约日期: 周" << of.m_order_data[i]["date"];
            std::cout << " 时段: " << (of.m_order_data[i]["interval"] == "1" ? "上午": "下午");
            std::cout << " 机房: " << (of.m_order_data[i]["room_id"]);

            std::stringstream status_ss;
            status_ss << " 状态: "; // 0 取消预约 1 审核中 2 已预约 -1 预约失败
            if(of.m_order_data[i]["status"] == "1") {
                status_ss << "审核中";
            }
            std::cout << status_ss.str() << std::endl;
        }
        
    }

    std::cout << "请输入审核的预约记录，0代表返回" << std::endl;

    int select = 0;
    int ret = 0;
    while(true) {
        std::cin >> select;
        if(select >= 0 && select <= v.size()) {
            if(select == 0) {
                break;
            } else {
                std::cout << "请输入审核结果" << std::endl;
                std::cout << "1.通过" << std::endl;
                std::cout << "2.不通过" << std::endl;

                std::cin >> ret;
                if(ret == 1) {
                    of.m_order_data[v[select-1]]["status"] = "2";
                } else {
                    of.m_order_data[v[select-1]]["status"] = "-1";
                }
                of.update_order();
                std::cout << "审核完毕" << std::endl;
                break;
            }
        }
        std::cout << "输入有误，请重新输入" << std::endl;
    }

    Funcs::pause();
    Funcs::clear();
}