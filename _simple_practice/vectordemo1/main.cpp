#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <cstdlib>
#include <algorithm>
using std::for_each;
using std::begin;
using std::end;

class Person {
    public:
        Person(string name, int age): m_Name(name), m_Age(age) {}
        string m_Name;
        int m_Age;
};

int main(void) {

    vector<Person> v;
    Person p("张三", 23);
    Person p1("李四", 22);
    Person p2("王五", 21);
    Person p3("赵六", 20);
    v.emplace_back(p);
    v.emplace_back(p1);
    v.emplace_back(p2);
    v.emplace_back(p3);

    for_each(begin(v), end(v), [](const Person& p) {
        cout << "姓名: " << p.m_Name << " 年龄: " << p.m_Age << endl; 
    });

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}

