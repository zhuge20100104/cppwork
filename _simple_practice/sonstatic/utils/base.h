#ifndef _BASE_H_
#define _BASE_H_
#include <iostream>

using std::cout;
using std::endl;

class Base {
    public:
        static int a;
        
        static void func() {
            cout << "Base的static func()" << endl;
        }
        
        static void func(int a) {
            cout << "Base的static func(int)" << endl;
        }

};


int Base::a = 100;

#endif
