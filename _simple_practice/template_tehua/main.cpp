#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

class Person
{
public:
    Person(string name, int age) : m_Name(name), m_Age(age) {}

    string m_Name;
    int m_Age;
};

bool operator==(const Person& p1, const Person &p2)
{
    if (p1.m_Name == p2.m_Name && p1.m_Age == p2.m_Age)
    {
        return true;
    }
    return false;
}

// 写一个Person类的模板特化，或者重载等于操作符都可以
// 我觉得这里重载 == 操作符更合理
// void myCompare(const Person& a, const Person& b) {
//     if(a.m_Name == b.m_Name && a.m_Age == b.m_Age) {
//         cout << "a==b" << endl;
//     } else {
//         cout << "a!=b" << endl;
//     }
// }

template <typename T>
void myCompare(const T &a, const T &b)
{
    if (a == b)
    {
        cout << "a==b" << endl;
    }
    else
    {
        cout << "a!=b" << endl;
    }
}

int main(void)
{
    myCompare(10, 10);
    Person p("张三", 11);
    Person p2("张三", 12);
    myCompare(p, p2);
}