#ifndef _FREDRIC_STUDENT_H_
#define _FREDRIC_STUDENT_H_

#include "beans/identity.h"
#include "beans/computer_room.h"

#include <vector>


struct student: public identity {
    student();
    student(int id, std::string name, std::string pwd);
    virtual void oper_menu();

    // 申请预约
    void apply_order();
    // 查看我的预约
    void show_my_order();
    // 查看所有预约
    void show_all_order();
    // 取消预约
    void cancel_order();
    // 学生学号
    int m_id;

    std::vector<computer_room> v_coms;
};
#endif