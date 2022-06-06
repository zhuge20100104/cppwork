#ifndef _ABS_DRINK_H_
#define _ABS_DRINK_H_

class AbsDrink
{
public:
    // 煮水
    virtual void Boil() = 0;

    // 冲泡
    virtual void Brew() = 0;

    // 倒入杯中
    virtual void PourInCup() = 0;

    // 加入辅料
    virtual void PutSomething() = 0;

    void MakeDrink();
};

#endif