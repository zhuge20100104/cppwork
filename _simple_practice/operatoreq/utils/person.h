#ifndef _PERSON_H_
#define _PERSON_H_
#include <iostream>
using std::cout;
using std::endl;

class Person {
    public:
        Person(int age);
        Person(const Person& p);
        ~Person();
        Person& operator=(Person& p);

    private:
        int *mAge;
};
#endif 
