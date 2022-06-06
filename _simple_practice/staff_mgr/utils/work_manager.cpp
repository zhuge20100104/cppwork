#include "work_manager.h"


WorkManager::WorkManager() {
    // 清空原有数据
    this->m_EmpArray.clear();

    INIT_FILE_PTR(ifstream, ifs);
    ifs->open(FILE_NAME, std::ios::in);

    if(!ifs->is_open()) {
        cout << "文件不存在" << endl;
        this->m_FileIsEmpty = true;
        this->m_EmpArray.clear();
        return;
    }

    char ch;
    *ifs >> ch;
    if(ifs->eof()) {
        cout << "文件为空!" << endl;
        this->m_FileIsEmpty = true;
        this->m_EmpArray.clear();
        return;
    }

    // 获取员工个数
    this->m_EmpNum = this->get_EmpNum();  // 更新成员属性
    
    // 预分配大小
    this->m_EmpArray.resize(this->m_EmpNum);
    
    // 初始化容器
    this->init_Emp();
}

WorkManager::~WorkManager() {
     // 释放vector内存
    this->m_EmpArray.clear();
}


void WorkManager::showMenu() {
    cout << "*****************************************************" << endl;
    cout << "********** 欢迎使用职工管理系统! *********************" << endl;
    cout << "**********     0.退出管理程序 ************************" << endl;
    cout << "**********     1.增加职工信息 ************************" << endl;
    cout << "**********     2.显示职工信息 ************************" << endl;
    cout << "**********     3.删除离职职工 ************************" << endl;
    cout << "**********     4.修改职工信息 ************************" << endl;
    cout << "**********     5.查找职工信息 ************************" << endl;
    cout << "**********     6.按照编号排序 ************************" << endl;
    cout << "**********     7.清空所有文档 ************************" << endl;
    cout << "*****************************************************" << endl;
    cout << endl;
}

void WorkManager::Add_Emp() {
    cout << "请输入增加的职工数量: " << endl;
    int addNum = 0;
    cin >> addNum;

    // 处理错误的输入
    if(addNum <= 0) {
        cout << "输入有误" << endl;
        this->pause();
        this->clearScreen();
        return;
    }

    for(int i=0; i<addNum; i++) {
        int id;
        string name;
        int dSelect;

        cout << "请输入第 " << i + 1 << " 个新职工编号: " << endl;
        cin >> id;

        cout << "请输入第 " << i + 1 << " 个新职工姓名: " << endl;
        cin >> name;

        cout << "请选择该职工的岗位: " << endl;
        cout << "1、普通职工" << endl;
        cout << "2、经理" << endl;
        cout << "3、老板" << endl;
        cin >> dSelect;

        WorkerPtr worker;
        switch (dSelect)
        {
        case 1: // 普通员工
            worker = WorkerPtr(new Employee(id, name, 1));
            break;
        case 2: // 经理
            worker = WorkerPtr(new Manager(id, name, 2));
            break;
        case 3: // 老板
            worker = WorkerPtr(new Boss(id, name, 3));
            break;
        default:
            break;
        }

        m_EmpArray.emplace_back(worker);
    }

    cout << "成功添加 " << addNum << " 名新职工!" << endl;
    this->m_EmpNum += addNum;
    // 保存到文件
    this->save();
    this->m_FileIsEmpty = false;
    this->pause();
    this->clearScreen();
}

void WorkManager::init_Emp() {
    INIT_FILE_PTR(ifstream, ifs);

    ifs->open(FILE_NAME, std::ios::in);

    int id;
    string name;
    int dId;

    int index = 0;

    while(*ifs >> id && *ifs >> name && *ifs >> dId) {
        WorkerPtr worker;
        if(dId == 1) {
            worker = WorkerPtr(new Employee(id, name, dId));
        } else if(dId == 2) {
            worker = WorkerPtr(new Manager(id, name, dId));
        } else {
            worker = WorkerPtr(new Boss(id, name, dId));
        } 
        this->m_EmpArray[index] = worker;
        ++index;
    }
}


void WorkManager::show_Emp() {
    if(this->m_FileIsEmpty) {
        cout << "文件不存在或记录为空" << endl;
    }else {
        for(WorkArr::iterator b = m_EmpArray.begin(), e = m_EmpArray.end(); b != e; ++b) {
            (*b)->showInfo();
        }  
    }
    this->pause();
    this->clearScreen();
}

void WorkManager::Del_Emp() {
    if(this->m_FileIsEmpty) {
        cout << "文件不存在或记录为空" << endl;
    } else {
        cout << "请输入想要删除的职工号: " << endl;
        int id = 0;
        cin >> id;
        auto findIt = this->isExist(id);

        // 找到了
        if(findIt != m_EmpArray.end()) {
            m_EmpArray.erase(findIt);
            this->m_EmpNum --;
            this->save();
            cout << "删除成功 " << endl;    
        }else {
            cout << "删除失败，未找到该员工" << endl; 
        }
    }

    this->pause();
    this->clearScreen();
}

void WorkManager::Mod_Emp() {
    if(this->m_FileIsEmpty) {
        cout << "文件不存在或记录为空!" << endl;
    } else {
        cout << "请输入要修改的职工编号: " << endl;
        int id;
        cin >> id;
        auto findIt = this->isExist(id);
        if(findIt != m_EmpArray.end()) {
            // 清空原有shared_ptr数据
            WorkerPtr& oldWorker = *findIt;
            oldWorker.reset();
            int newId = 0;
            string newName = "";
            int dSelect = 0;
            cout << "查到: " << id << "号职工，请输入新职工号: " << endl;
            cin >> newId;
            cout << "请输入新姓名: " << endl;
            cin >> newName;
            cout << "请输入岗位: " << endl;
            cout << "1、普通职工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            cin >> dSelect;

            switch (dSelect)
            {
            case 1:
                oldWorker = WorkerPtr(new Employee(newId, newName, dSelect));
                break;
            case 2:
                oldWorker = WorkerPtr(new Manager(newId, newName, dSelect));
                break;
            case 3:
                oldWorker = WorkerPtr(new Boss(newId, newName, dSelect));
                break;
            default:
                break;
            }

            cout << "修改成功!" << oldWorker->m_Id << endl;
            this->save();
        } else {
            cout << "修改失败，查无此人" << endl;
        }
    }

    this->pause();
    this->clearScreen();
}

void WorkManager::Find_Emp() {
    if(this->m_FileIsEmpty) {
        cout << "文件不存在或记录为空" << endl;
    }else {
        cout << "请输入要查找的方式: " << endl;
        cout << "1、按职工编号查找" << endl;
        cout << "2、按职工姓名查找" << endl;

        int select = 0;
        cin >> select;

        // 按工号查找
        if(select == 1) {
            int id;
            cout << "请输入要查找的职工编号: " << endl;
            cin >> id;

            auto findIt = isExist(id);
            // 找到了
            if(findIt != m_EmpArray.end()) {
                cout << "查找成功!该职工信息如下: " << endl;
                (*findIt)->showInfo();
            }else {
                cout << "查找失败，查无此人" << endl;
            }
        }else if(select == 2) {  //按姓名查找
            string name;
            cout << "请输入要查找的姓名: " << endl;
            cin >> name;

            bool flag = false;
            for(auto b = m_EmpArray.begin(), e = m_EmpArray.end(); b != e; ++b) {
                if((*b)->m_Name == name) {
                    flag = true;
                    cout << "查找成功，职工编号为: "
                        << (*b)->m_Id 
                        << " 号的信息如下: " << endl;
                    (*b)->showInfo();
                    break;    
                }
            }

            if(flag == false) {
                cout << "查找失败，查无此人" << endl;
            }
        }else {
            cout << "输入选项有误" << endl;
        }
    }

    this->pause();
    this->clearScreen();
}

void WorkManager::Sort_Emp() {
    if(this->m_FileIsEmpty) {
        cout << "文件不存在或记录为空" << endl;
        this->pause();
        this->clearScreen();
        return;
    } 

    cout << "请选择排序方式: " << endl;
    cout << "1、按职工号进行升序" << endl;
    cout << "2、按职工号进行降序" << endl;

    int select = 0;
    cin >> select;

    int size = m_EmpArray.size();
    for(int i = 0; i<size; ++i) {
        int minOrMax = i;

        for(int j=i+1; j<size; ++j) {
            if(select == 1) { // 升序寻找最小值
                if(m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id) {
                    minOrMax = j;
                }
            } else { // 降序寻找最大值
                if(m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id) {
                    minOrMax = j;
                }
            }
        }

        if(i != minOrMax) {
            WorkerPtr tmp = m_EmpArray[i];
            m_EmpArray[i] = m_EmpArray[minOrMax];
            m_EmpArray[minOrMax] = tmp;
        }
    }

    cout << "排序成功，排序后结果为: " << endl;
    this->save();
    this->show_Emp();
}

void WorkManager::Clean_File() {
    cout << "确认清空?" << endl;
    cout << "1、确认" << endl;
    cout << "2、返回" << endl;

    int select = 0;
    cin >> select;

    if(select == 1) {
        INIT_FILE_PTR(ofstream, ofs);
        ofs->open(FILE_NAME, std::ios::trunc);
        this->m_EmpArray.clear();
        m_EmpNum = 0;
        m_FileIsEmpty = true;
        cout << "清空成功!" << endl;
    }    

    this->pause();
    this->clearScreen();
}

WorkArr::iterator WorkManager::isExist(int id) {
    for(auto b = m_EmpArray.begin(), e = m_EmpArray.end(); b != e; ++b) {
        if((*b)->m_Id == id) {
            return b;
        }
    }
    return m_EmpArray.end();
}

void WorkManager::save() {
    INIT_FILE_PTR(ofstream, ofs);
    ofs->open(FILE_NAME, std::ios::out);
    for(int i=0; i<this->m_EmpArray.size(); i++) {
        *ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << endl;
    }
}

int WorkManager::get_EmpNum() {
    INIT_FILE_PTR(ifstream, ifs);
    ifs->open(FILE_NAME, std::ios::in);

    int id;
    string name;
    int dId;

    int num = 0;
    while(*ifs >> id && *ifs >> name && *ifs >> dId) {
        // 记录人数
        num ++;
    }
    return num;
}

void WorkManager::clearScreen() {
    string clearStr = "clear";
#ifdef WINDOWS
    clearStr = "cls";
#endif
    system(clearStr.c_str());
}

void WorkManager::pause() {
    cout << "请按任意键继续..." << endl;
    getchar();
    getchar();
}

void WorkManager::exitSystem() {
    cout << "欢迎下次使用" << endl;
    this->pause();
    exit(0);
}