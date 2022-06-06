#ifndef _FREDRIC_MANAGER_H_
#define _FREDRIC_MANAGER_H_
#include "beans/identity.h"
#include "beans/student.h"
#include "beans/teacher.h"
#include "beans/computer_room.h"

#include <vector>

struct manager: public identity {
    manager();
    manager(std::string name, std::string pwd);
    
    virtual void oper_menu();
    // 添加账号
    void add_person();
    // 查看账号
    void show_person();
    // 查看机房信息
    void show_computer();
    // 清空预约记录
    void clean_file();

    // 初始化容器
    void init_vector();

    bool check_repeat(int id, int type);

    std::vector<student> v_stus;
    std::vector<teacher> v_teas;
    std::vector<computer_room> v_coms;
};
#endif