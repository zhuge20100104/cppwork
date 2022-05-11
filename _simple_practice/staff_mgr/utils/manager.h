#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "worker.h"

class Manager: public Worker {
    public:
        Manager(int id, string name, int dId);
        virtual void showInfo();
        virtual string getDeptName();

};

#endif