#include "beans/manager.h"
#include "utils/consts.h"
#include "utils/func.h"

#include <iostream>
#include <fstream>
#include <algorithm>

manager::manager() {}

manager::manager(std::string name, std::string pwd) {
    m_name = name;
    m_pwd = pwd;
    
    init_vector();

    // 读取机房信息
    std::ifstream ifs;
    ifs.open(computer_file, std::ios::in);
    computer_room c;
    while(ifs >> c.m_room_id && ifs >> c.m_max_num) {
        v_coms.emplace_back(std::move(c));
    }
    std::cout << "当前机房数量为: " << v_coms.size() << std::endl;
    ifs.close();
}

void manager::init_vector() {
    std::ifstream ifs;
    ifs.open(student_file, std::ios::in);
    if(!ifs.is_open()) {
        std::cout << "读取文件失败" << std::endl;
        return;
    }

    v_stus.clear();
    v_teas.clear();

    student s;
    while(ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_pwd) {
        v_stus.emplace_back(std::move(s));
    }

    std::cout << "当前学生数量为: " << v_stus.size() << std::endl;
    ifs.close();

    ifs.open(teacher_file, std::ios::in);

    if(!ifs.is_open()) {
        std::cout << "读取教师文件失败" << std::endl;
        return;
    }
    teacher t;
    while(ifs >> t.m_emp_id && ifs >> t.m_name && ifs >> t.m_pwd) {
        v_teas.emplace_back(std::move(t));
    }
    
    std::cout << "当前教师数量为: " << v_teas.size() << std::endl;
    ifs.close();
}

void manager::oper_menu() {
    std::cout << "欢迎管理员: " << m_name << "登录!" << std::endl;
    std::cout << "\t\t---------------------------------------------\n";
    std::cout << "\t\t|                                            |\n";
    std::cout << "\t\t|               1.添加账号                    |\n";
    std::cout << "\t\t|                                            |\n";
    std::cout << "\t\t|               2.查看账号                     |\n";
    std::cout << "\t\t|                                            |\n";
    std::cout << "\t\t|               3.查看机房                     |\n";
    std::cout << "\t\t|                                            |\n";
    std::cout << "\t\t|               4.清空预约                     |\n";
    std::cout << "\t\t|                                            |\n";
    std::cout << "\t\t|               5.注销登录                    |\n";
    std::cout << "\t\t|                                            |\n";
    std::cout << "\t\t---------------------------------------------\n";
    std::cout << "请选择您的操作: " << std::endl;
}

// 添加账号
void manager::add_person() {
    std::cout << "请输入添加账号的类型" << std::endl;
    std::cout << "1.添加学生" << std::endl;
    std::cout << "2.添加老师" << std::endl;

    std::string error_tip;
    std::string filename;
    std::string tip;
    std::ofstream ofs;

    int select = 0;
    std::cin >> select;

    if(select == 1) {
        filename = student_file;
        tip = "请输入学号:";
        error_tip = "学号重复，清重新输入";
    } else {
        filename = teacher_file;
        tip = "请输入职工编号:";
        error_tip = "职工号重复，请重新输入";
    }

    ofs.open(filename, std::ios::out | std::ios::app);
    int id;
    std::string name;
    std::string pwd;
   
    std::cout << tip << std::endl; 
    while(true) {
        std::cin >> id;
        bool ret = check_repeat(id, select);
        if(ret) { // 有重复
            std::cout << error_tip << std::endl;
        } else {
            break;
        }
    }

    std::cout << "请输入姓名:" << std::endl; 
    std::cin >> name;
    
    std::cout << "请输入密码:" << std::endl; 
    std::cin >> pwd;

    ofs << id << " " << name << " " << pwd << " " << std::endl;
    std::cout << "添加成功" << std::endl; 

    ofs.close();
    Funcs::pause();
    Funcs::clear();

    init_vector();
}

// 查看账号
void manager::show_person() {
    std::cout << "请选择查看内容:" << std::endl;
    std::cout << "1.查看所有学生" << std::endl;
    std::cout << "2.查看所有老师" << std::endl;

    int select = 0;
    std::cin >> select;
    if(select == 1) { //查看所有学生信息
        std::for_each(v_stus.begin(), v_stus.end(), [](const student& s){
            std::cout << "学号: " << s.m_id << " 姓名: " << s.m_name << " 密码:" << s.m_pwd << std::endl;
        });
    }else { //查看所有老师信息
        std::for_each(v_teas.begin(), v_teas.end(), [](const teacher& t){
            std::cout << "职工号: " << t.m_emp_id << " 姓名: " << t.m_name << " 密码: " << t.m_pwd << std::endl;
        });
    }
    Funcs::pause();
    Funcs::clear();
}

// 查看机房信息
void manager::show_computer() {
    std::cout << "机房信息如下: " << std::endl;
    for(auto&& com: v_coms) {
        std::cout << "机房编号: " << com.m_room_id << " 机房最大容量: " << com.m_max_num << std::endl;
    }
    Funcs::pause();
    Funcs::clear();
}

// 清空预约记录
void manager::clean_file() {
    std::ofstream ofs {s_order_file, std::ios::trunc};
    ofs.close();
    std::cout << "清空成功!" << std::endl;
    Funcs::pause();
    Funcs::clear();
}

bool manager::check_repeat(int id, int type) {
    if(type == 1) {
        for(auto&& s: v_stus) {
            if(s.m_id == id) {
                return true;
            }
        }
    } else {
        for(auto&& t: v_teas) {
            if(t.m_emp_id == id) {
                return true;
            }
        }
    }
    return false;
}