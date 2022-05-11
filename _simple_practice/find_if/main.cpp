#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;
#include <algorithm>
using std::find_if;
#include <string>
using std::string;
#include <cstdlib>
using std::begin;
using std::end;

class Person {
    public: 
        Person(string name, int age): m_Name(name), m_Age(age) {}
        string m_Name;
        int m_Age;
};

int main(void) {

    vector<int> v;
    for(int i=0; i<10; i++) {
        v.emplace_back(i);
    }

    auto greatFiveIt = find_if(begin(v), end(v), [](const int& val) {
        return val > 5;
    });

    if(greatFiveIt != end(v)) {
        cout << "找到了: " << *greatFiveIt << endl;
    }else {
        cout << "没找到" << endl;
    }

    vector<Person> vPersons;
    Person p1("张三", 21);
    Person p2("李四", 22);
    Person p3("王五", 23);
    Person p4("赵六", 24);

    vPersons.emplace_back(p1);
    vPersons.emplace_back(p2);
    vPersons.emplace_back(p3);
    vPersons.emplace_back(p4);
    auto findPersonIt = find_if(begin(vPersons), end(vPersons), [] (const Person& p) {
        return p.m_Age > 22;
    });

    if(findPersonIt != end(vPersons)) {
        cout << "找到姓名: " << findPersonIt->m_Name << " 年龄: " << findPersonIt->m_Age << endl;
    } else {
        cout << "没找到" << endl;
    }

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}