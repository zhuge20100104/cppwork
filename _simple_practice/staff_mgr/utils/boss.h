#ifndef _BOSS_H_
#define _BOSS_H_

#include "worker.h"

class Boss: public Worker {
    public:
        Boss(int id, string name, int dId);
        virtual void showInfo();
        virtual string getDeptName();

};

#endif