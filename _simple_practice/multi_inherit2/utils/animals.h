#ifndef _ANIMALS_H_
#define _ANIMALS_H_

// 动物基类
class Animal {
    public:
        int m_Age;
};

// 虚继承，在内存中生成一个vbptr, virtual base pointer,指向基类
// 羊类
class Sheep: virtual public Animal {};

// 虚继承，在内存中生成一个vbptr, virtual base pointer,指向基类
// 驼类
class Tuo: virtual public Animal {};

// 羊驼类
class SheepTuo: public Sheep, public Tuo {};

#endif