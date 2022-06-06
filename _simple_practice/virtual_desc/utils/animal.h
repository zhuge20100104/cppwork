#ifndef _ANIMAL_H_
#define _ANIMAL_H_

#include <iostream>
using std::cout;
using std::endl;



class Animal {

public:
    Animal() {}
    virtual ~Animal() = 0;
    virtual void Speak() = 0;
};

Animal::~Animal() {
    cout << "Animal类的虚析构函数被调用..." << endl;
}

#endif