#ifndef _PERSON_HPP_
#define _PERSON_HPP_

#include <iostream>
using std::cout;
using std::endl;

template <class T1, class T2>
class Person {

    // 全局函数类内实现
    friend void PrintPerson(const Person<T1, T2>& p) {
        cout << "姓名: " << p.m_Name << " 年龄: " << p.m_Age << endl;
    }

    // 全局函数类外实现
    template <class U, class V>
    friend void PrintPerson2(const Person<U, V>& p);

    public:
        Person(T1 name, T2 age): m_Name(name), m_Age(age) {}
        
        T1 m_Name;
        T2 m_Age;
};

template <class T1, class T2>
void PrintPerson2(const Person<T1, T2>& p) {
    cout << "姓名: " << p.m_Name << " 年龄: " << p.m_Age << endl;
}

#endif