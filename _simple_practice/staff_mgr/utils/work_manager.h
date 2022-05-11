#ifndef _WORK_MANAGER_H_
#define _WORK_MANAGER_H_

#include <iostream>
using std::cout;
using std::endl;
#include "consts.h"
#include <string>
using std::string;
#include <cstdlib>
#include <memory>
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <vector>
using std::cin;
#include <fstream>
using std::ofstream;
using std::ifstream;
#include <algorithm>

using WorkerPtr = std::shared_ptr<Worker>;
using WorkArr = std::vector<WorkerPtr>;

class WorkManager {
    public:
        WorkManager();
        ~WorkManager();
        // 显示菜单功能实现
        void showMenu();
        // 退出系统
        void exitSystem();

        // 添加职工功能
        void Add_Emp();

        // 存文件
        void save();

        // 获取员工数量
        int get_EmpNum();

        // 初始化员工信息
        void init_Emp();

        // 显示员工信息功能
        void show_Emp();

        // 删除员工信息
        void Del_Emp();

        // 修改员工信息
        void Mod_Emp();

        // 查找职工信息
        void Find_Emp();

        // 排序职工信息
        void Sort_Emp();

        // 清空所有员工信息
        void Clean_File();

        WorkArr::iterator isExist(int id);

        // 清空屏幕
        void clearScreen();
        // 暂停屏幕，请按任意键继续
        void pause();

    private:
        // 标志文件是否为空
        bool m_FileIsEmpty;
        WorkArr m_EmpArray;
        int m_EmpNum;
};
#endif