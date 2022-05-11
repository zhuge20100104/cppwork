#ifndef _PERSON_H_
#define _PERSON_H_ 

#include <iostream>
using std::cout;
using std::ostream;

class Person {
    friend ostream& operator<<(ostream& cout, const Person& p);
    public:
        Person(int a, int b);
    private:
        int mA;
        int mB;
};
#endif
