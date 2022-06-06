#include "singleton.hpp"
#include <iostream>
using std::cout;
using std::endl;

struct Person
{
    Person(): m_Name("呵呵"), m_Age(20) {

    }

    Person(std::string name, int age): m_Name(name), m_Age(age) {}

    std::string m_Name;
    int m_Age;
};

struct Visitor {
    Visitor(): m_Name("呵呵"), m_Age(20) {

    }
    std::string m_Name;
    int m_Age;
};

int main(void) {
    shared_ptr<int> sInt = Singleton<int>::Instance(100);
    cout << *sInt << endl;

    // 两次调用都获得 张三
    cout << "Person类相关信息输出: " << endl;
    shared_ptr<Person> p = Singleton<Person>::Instance("张三", 30);
    cout << "姓名: " << p->m_Name << " 年龄: " << p->m_Age << endl;
    shared_ptr<Person> p2 = Singleton<Person>::Instance();
    cout << "姓名: " << p2->m_Name << " 年龄: " << p2->m_Age << endl;

    // 调用无参构造函数
    cout << "Visitor类相关信息输出: " << endl;
    shared_ptr<Visitor> v = Singleton<Visitor>::Instance();
    cout << "姓名: " << v->m_Name << " 年龄: " << v->m_Age << endl;
}