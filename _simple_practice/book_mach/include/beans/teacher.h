#ifndef _FREDRIC_TEACHER_H_
#define _FREDRIC_TEACHER_H_

#include <string>
#include "beans/identity.h"

struct teacher: public identity {
    teacher();
    teacher(int emp_id, std::string name, std::string pwd);
    virtual void oper_menu();

    // 查看所有预约
    void show_all_order();
    // 审核预约
    void valid_order();

    int m_emp_id;
};
#endif