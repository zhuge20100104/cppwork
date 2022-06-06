#ifndef _TEA_H_
#define _TEA_H_

#include "absdrink.h"
#include <iostream>
using std::cout;
using std::endl;

class Tea : public AbsDrink {
public:
    virtual void Boil();

    // 冲泡
    virtual void Brew();

    // 倒入杯中
    virtual void PourInCup();

    // 加入辅料
    virtual void PutSomething();
};
#endif