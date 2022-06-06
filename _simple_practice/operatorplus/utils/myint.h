#ifndef _MY_INT_H_
#define _MY_INT_H_
#include <iostream>
using std::ostream;

class MyInt {
    friend ostream& operator<<(ostream& cout, const MyInt& m);
    public:
        MyInt();
        MyInt(int a);
        MyInt& operator++(); // 重载前置递增运算符
        MyInt operator++(int); // 重载后置递增运算符 

    private:
        int mNum;
};
#endif
