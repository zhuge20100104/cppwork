#ifndef _PERSON_HPP_
#define _PERSON_HPP_
#include <iostream>
using std::cout;
using std::endl;

template <class T1, class T2>
class Person {
    public:
        Person(T1 name, T2 age);
        void showPerson();
        T1 m_Name;
        T2 m_Age;
        
};


template <class T1, class T2> 
Person<T1, T2>::Person(T1 name, T2 age): m_Name(name), m_Age(age) {} 

template <class T1, class T2>
void Person<T1, T2>::showPerson() {
    cout << "姓名: " << m_Name << " 年龄: " << m_Age << endl;
}

#endif