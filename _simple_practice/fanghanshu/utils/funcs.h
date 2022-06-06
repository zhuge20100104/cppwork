#ifndef _FUNCS_H_
#define _FUNCS_H_

#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;


class MyPrint{
    public:
        void operator()(string test) {
            cout << test << endl;            
        }
};

class MyAdd {
    public:
        int operator()(int a, int b) {
            return a + b;
        }
};
#endif
