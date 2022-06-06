#ifndef _WORKER_H_
#define _WORKER_H_

#include <string>
using std::string;

class Worker {
    public:
        Worker(string name, int salary): m_Name(name), m_Salary(salary) {}
        string m_Name;
        int m_Salary;
};
#endif