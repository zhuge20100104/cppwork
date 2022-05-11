#ifndef _SON_H_
#define _SON_H_
#include "base.h"

class Son: public Base {
    public:
        static int a;
        
        static void func() {
            cout << "Son的static func()" << endl;
        }

        static void func(int a) {
            cout << "Son的static func(int)" << endl;
        }
};

int Son::a = 200;
#endif 
