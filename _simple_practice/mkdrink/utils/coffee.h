#ifndef _COFFEE_H_
#define _COFFEE_H_

#include <iostream>
using std::cout;
using std::endl;

#include "absdrink.h"

class Coffee : public AbsDrink
{
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