#ifndef _WORKER_H_
#define _WORKER_H_

#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;

class Worker {
    public:
        virtual ~Worker() {}
        // 显示个人信息
        virtual void showInfo() = 0;
        // 获取岗位名称
        virtual string getDeptName() = 0;

        int m_Id; // 职工编号
        string m_Name; // 职工姓名
        int m_DeptId; // 职工所在部门编号
};
#endif