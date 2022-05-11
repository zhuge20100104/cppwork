#ifndef _OBJS_H_
#define _OBJS_H_

#include <iostream>
using std::cout;
using std::endl;


class Base {
    public:
        virtual void func() = 0;
};

class Son: public Base {
    public:
        virtual void func() {
            cout << "func 函数调用" << endl;
        }
};

#endif