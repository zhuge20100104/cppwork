#ifndef _LENOVO_H_
#define _LENOVO_H_

#include "computer.h"
#include <iostream>
using std::cout;
using std::endl;

class LenovoCPU: public CPU {
    public:
         virtual void calculate();
};

void LenovoCPU::calculate() {
    cout << "Lenovo的CPU开始计算了" << endl;
}

class LenovoVideocard: public VideoCard {
    public:
         virtual void display();
};

void LenovoVideocard::display() {
    cout << "Lenovo的显示器开始显示了" << endl;
}

class LenovoMemory: public Memory {
    public:
        virtual void storage();
};

void LenovoMemory::storage() {
    cout << "Lenovo的内存开始存储了" << endl;
}

#endif