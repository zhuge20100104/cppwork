#ifndef _INTEL_H_
#define _INTEL_H_

#include "computer.h"
#include <iostream>
using std::cout;
using std::endl;

class IntelCPU: public CPU {
    public:
         virtual void calculate();
};

void IntelCPU::calculate() {
    cout << "Intel的CPU开始计算了" << endl;
}

class IntelVideocard: public VideoCard {
    public:
         virtual void display();
};

void IntelVideocard::display() {
    cout << "Intel的显示器开始显示了" << endl;
}

class IntelMemory: public Memory {
    public:
        virtual void storage();
};

void IntelMemory::storage() {
    cout << "Intel的内存开始存储了" << endl;
}

#endif