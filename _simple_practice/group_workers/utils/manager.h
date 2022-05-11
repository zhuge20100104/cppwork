#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "worker.h"

#include <vector>
#include <memory>
#include <string>
using std::string;
#include <map>
#include <algorithm>
#include <iostream>
using std::cout;
using std::for_each;
using std::endl;
#include <exception>
using std::exception;

#include "consts.h"

using WorkerPtr = std::shared_ptr<Worker>;
using WorkerArr = std::vector<std::shared_ptr<Worker>>;
using WorkerIt = WorkerArr::iterator; 

using WorkerMap = std::multimap<int, std::shared_ptr<Worker> >;
using WorkerMapIt = WorkerMap::iterator;

class Manager {
    public:
        Manager() {
            initWorkers();
        }

        // 设置用户组
        void setWorkerGroup() {
            for_each(begin(m_Workers), end(m_Workers), [this](const WorkerPtr& worker) {
                int group = rand() % 3;  // 0, 1, 2
                m_WorkerMap.emplace(group, worker);
            });
        }   

        // 按组显示用户
        void showWorkerByGroup() {
           showWorkersInAGroup(CEHUA, "策划部");
           showWorkersInAGroup(MEISHU, "美术部");
           showWorkersInAGroup(YANFA, "研发部");      
        }

    private:
        void initWorkers() {
            string nameSeed = "ABCDEFGHIJ";
            int len = nameSeed.size();

            for(int i=0; i<len; ++i) {
                string name = "员工";
                name += nameSeed[i];
                int salary = rand() % 10001 + 10000;  // 10000 ~ 20000
                m_Workers.emplace_back(WorkerPtr(new Worker(name, salary)));
            }
        }

        void showWorkersInAGroup(int group, string groupName) {
            auto mapIt = m_WorkerMap.find(group);
            int count = m_WorkerMap.count(group);
            int index = 0;
            cout << groupName << "人员相关信息: " << endl;
            for(WorkerMapIt it = mapIt, ite = m_WorkerMap.end(); it!=ite && index < count ; ++it, ++index) {
                cout << "姓名: " << it->second->m_Name << " 工资: " << it->second->m_Salary << endl;
            }
        }

        WorkerArr m_Workers;
        WorkerMap m_WorkerMap;
};

#endif