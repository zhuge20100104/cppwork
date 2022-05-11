#include "beans/student.h"
#include "utils/consts.h"
#include "utils/func.h"
#include "beans/order_file.h"

#include <iostream>
#include <fstream>
#include <sstream>

student::student() {

}

student::student(int id, std::string name, std::string pwd) {
    m_id = id;
    m_name = name;
    m_pwd = pwd;

    std::ifstream ifs;
    ifs.open(computer_file, std::ios::in);

    computer_room c;
    while(ifs >> c.m_room_id && ifs >> c.m_max_num) {
        v_coms.emplace_back(std::move(c));
    }
    ifs.close();
}

void student::oper_menu() {
    std::cout << "欢迎学生代表: " << m_name << "登录!" << std::endl;
    std::cout << "\t\t---------------------------------------------\n";
    std::cout << "\t\t|                                            |\n";
    std::cout << "\t\t|               1.申请预约                    |\n";
    std::cout << "\t\t|                                            |\n";
    std::cout << "\t\t|               2.查看我的预约                 |\n";
    std::cout << "\t\t|                                            |\n";
    std::cout << "\t\t|               3.查看所有预约                 |\n";
    std::cout << "\t\t|                                            |\n";
    std::cout << "\t\t|               4.取消预约                     |\n";
    std::cout << "\t\t|                                            |\n";
    std::cout << "\t\t|               0.注销登录                    |\n";
    std::cout << "\t\t|                                            |\n";
    std::cout << "\t\t---------------------------------------------\n";
    std::cout << "请选择您的操作: " << std::endl;
}

// 申请预约
void student::apply_order() {
    std::cout << "机房开放时间为周一至周五!" << std::endl;
    std::cout << "请输入申请预约的时间:" << std::endl;

    std::cout << "1.周一" << std::endl;
    std::cout << "2.周二" << std::endl;
    std::cout << "3.周三" << std::endl;
    std::cout << "4.周四" << std::endl;
    std::cout << "5.周五" << std::endl;

    int date = 0;  // 周一 --> 周五
    int interval = 0; // 上午，下午
    int room = 0;  // 房间号

    while(true) {
        std::cin >> date;
        if(date >= 1 && date <= 5) {
            break;
        }
        std::cout << "输入有误，请重新输入" << std::endl;
    }

    std::cout << "请输入申请预约的时间段:" << std::endl;

    std::cout << "1.上午" << std::endl;
    std::cout << "2.下午" << std::endl;

    while(true) {
        std::cin >> interval;
        if(interval >= 1 && interval <= 2) {
            break;
        }
        std::cout << "输入有误，请重新输入" << std::endl;
    }

    std::cout << "请选择机房:" << std::endl;

    std::cout << "1号机房容量" << v_coms[0].m_max_num << std::endl;
    std::cout << "2号机房容量" << v_coms[1].m_max_num << std::endl;
    std::cout << "3号机房容量" << v_coms[2].m_max_num << std::endl;

    while(true) {
        std::cin >> room;
        if(room >= 1 && room <= 3) {
            break;
        }
        std::cout << "输入有误，请重新输入" << std::endl;
    }

    std::cout << "预约成功！审核中" << std::endl;
    
    std::ofstream ofs(s_order_file, std::ios::app);
    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "stu_id:" << m_id << " ";
    ofs << "stu_name:" << m_name << " ";
    ofs << "room_id:" << room << " ";
    ofs << "status:" << 1 << std::endl;

    ofs.close();

    Funcs::pause();
    Funcs::clear();
}

// 查看我的预约
void student::show_my_order() {
    order_file of;
    if(of.m_size == 0) {
        std::cout << "无预约记录" << std::endl;
        Funcs::pause();
        Funcs::clear();
        return;
    }

    for(int i=0; i<of.m_size; ++i) {
        // 是当前学生的订单
        if(std::atoi(of.m_order_data[i]["stu_id"].c_str()) == m_id) {
            std::cout << "预约日期: 周" << of.m_order_data[i]["date"];
            std::cout << " 时段: " << (of.m_order_data[i]["interval"] == "1" ? "上午": "下午");
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
    }

    Funcs::pause();
    Funcs::clear();
}

// 查看所有预约
void student::show_all_order() {
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

// 取消预约
void student::cancel_order() {
    order_file of;
    if(of.m_size == 0) {
        std::cout << "无预约记录" << std::endl;
        Funcs::pause();
        Funcs::clear();
        return;
    }

    std::cout << "审核中或者预约成功的记录可以取消，请输入取消的记录" << std::endl;

    // 所有能被取消的记录索引
    std::vector<int> v;
    int index = 1;

    for(int i=0; i<of.m_size; ++i) {
        // 是当前学生的订单
        if(std::atoi(of.m_order_data[i]["stu_id"].c_str()) == m_id) {
            if(of.m_order_data[i]["status"] == "1" || of.m_order_data[i]["status"] == "2") {
                v.push_back(i);
                std::cout << index ++ << "."; 
                std::cout << "预约日期: 周" << of.m_order_data[i]["date"];
                std::cout << " 时段: " << (of.m_order_data[i]["interval"] == "1" ? "上午": "下午");
                std::cout << " 机房: " << (of.m_order_data[i]["room_id"]);

                std::stringstream status_ss;
                status_ss << " 状态: "; // 0 取消预约 1 审核中 2 已预约 -1 预约失败
                if(of.m_order_data[i]["status"] == "1") {
                    status_ss << "审核中";
                } else if(of.m_order_data[i]["status"] == "2") {
                    status_ss << "预约成功";
                } 
                std::cout << status_ss.str() << std::endl;
            }
        }
    }

    std::cout << "请输入取消的记录，0代表返回" << std::endl;

    int select = 0;
    while(true) {
        std::cin >> select;
        if(select >= 0 && select <= v.size()) {
            if(select == 0) {
                break;
            } else {
                of.m_order_data[v[select-1]]["status"] = "0";
                of.update_order();
                std::cout << "已取消预约" << std::endl;
                break;
            }
        }
        std::cout << "输入有误，请重新输入" << std::endl;
    }

    Funcs::pause();
    Funcs::clear();
}