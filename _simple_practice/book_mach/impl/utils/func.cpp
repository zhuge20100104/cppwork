#include "utils/func.h"
#include "beans/identity.h"
#include "beans/student.h"
#include "beans/teacher.h"
#include "beans/manager.h"

#include <iostream>
#include <memory>
#include <fstream>

void Funcs::pause() {
#ifdef WINDOWS
    (void)std::system("pause");
#else
    (void)std::system("read");
#endif
}

void Funcs::clear() {
#ifdef WINDOWS
    (void)std::system("cls");
#else
    (void)std::system("clear");
#endif
}

void Funcs::login_in(std::string file_name, int type) {
    std::unique_ptr<identity> person = nullptr;
    std::ifstream ifs;
    ifs.open(file_name, std::ios::in);

    // 文件不存在的情况
    if(!ifs.is_open()) {
        std::cout << "文件不存在"  << std::endl;
        ifs.close();
        return;
    }

    int id = 0;
    std::string name;
    std::string pwd;

    if(type == 1) {
        std::cout << "请输入你的学号" << std::endl;
        std::cin >> id;
    } else if(type == 2) {
        std::cout << "请输入你的职工号" << std::endl;
        std::cin >> id;
    }
    std::cout << "请输入用户名:" << std::endl;
    std::cin >> name;
    std::cout << "请输入密码:" << std::endl;
    std::cin >> pwd;

    // 学生登录验证
    if(type == 1) {
        int f_id;
        std::string f_name;
        std::string f_pwd;
        while(ifs >> f_id && ifs >> f_name && ifs >> f_pwd) {
            if(id == f_id && name == f_name && pwd == f_pwd) {
                std::cout << "学生验证登录成功!" << std::endl;
                Funcs::pause();
                Funcs::clear();
                person = std::make_unique<student>(id, name, pwd);
                auto person_p = person.get();
                student_menu(person_p);
                return;
            }
        }
    } else if(type == 2) {
        // 教师登录验证
        int f_id;
        std::string f_name;
        std::string f_pwd;
        while(ifs >> f_id && ifs >> f_name && ifs >> f_pwd) {
            if(id == f_id && name == f_name && pwd == f_pwd) {
                std::cout << "教师验证登录成功!" << std::endl;
                Funcs::pause();
                Funcs::clear();
                person = std::make_unique<teacher>(id, name, pwd);
                auto person_p = person.get();
                teacher_menu(person_p);
                return;
            }
        }
    } else if(type == 3) {
        // 管理员登录验证
        std::string f_name;
        std::string f_pwd;
        while(ifs >> f_name && ifs >> f_pwd) {
            if(name == f_name && pwd == f_pwd) {
                std::cout << "管理员验证登录成功!" << std::endl;
                Funcs::pause();
                Funcs::clear();
                person = std::make_unique<manager>(name, pwd);
                auto person_p = person.get();
                manager_menu(person_p);
                return;
            }
        }
    }
    Funcs::pause();
    Funcs::clear();
    return;
}

void Funcs::manager_menu(identity* & man_) {
    while(true) {
        // 管理员菜单虚函数
        man_->oper_menu();
        manager* man = dynamic_cast<manager*>(man_);
        int select = 0;
        std::cin >> select;
        switch(select) {
            case 1: // 添加账号
                std::cout << "添加账号" << std::endl;
                man->add_person();
                break;
            case 2: // 查看账号
                std::cout << "查看账号" << std::endl;
                man->show_person();
                break;
            case 3: // 查看机房
                std::cout << "查看机房" << std::endl;
                man->show_computer();
                break;
            case 4:
                std::cout << "清空预约" << std::endl;
                man->clean_file();
                break;
            default:    
                std::cout << "注销成功" << std::endl;
                Funcs::pause();
                Funcs::clear();
                return;
        }
    }
}

void Funcs::student_menu(identity* & stu_) {
    while(true) {
        // 学生菜单
        stu_->oper_menu();

        student* stu = dynamic_cast<student*>(stu_);
        int select = 0;

        std::cin >> select;

        switch (select)
        {
        case 1: // 申请预约
            stu->apply_order();
            break;
        case 2: // 查看自身预约
            stu->show_my_order();
            break;
        case 3: // 查看所有预约
            stu->show_all_order();
            break;
        case 4: // 取消预约
            stu->cancel_order();
            break;
        default:
            std::cout << "注销成功" << std::endl;
            Funcs::pause();
            Funcs::clear();
            return;
        }
    }
}

void Funcs::teacher_menu(identity* & tea_) {
    while(true) {
        // 教师菜单
        tea_->oper_menu();
        teacher* tea = dynamic_cast<teacher*>(tea_);

        int select = 0;

        std::cin >> select;

        switch(select) {
            case 1: // 查看所有预约
                tea->show_all_order();
                break;
            case 2: // 审核预约
                tea->valid_order();
                break;
            default: // 退出
                std::cout << "注销成功" << std::endl;
                Funcs::pause();
                Funcs::clear();
                return;
        }
    }
}