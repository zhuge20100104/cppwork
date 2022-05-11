#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

#include "worker.h"

class Employee: public Worker {
    public:
        Employee(int id, string name, int dId);
        virtual void showInfo();
        virtual string getDeptName();

};
#endif