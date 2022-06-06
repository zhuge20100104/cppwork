#include <iostream>
using std::cout;
using std::endl;
#include <cstdlib>

#include <vector>
using std::vector;
#include <algorithm>
using std::find;
using std::for_each;
using std::begin;
using std::end;
#include <string>
using std::string;

// 初始化向量
void initVector(vector<int>& v) {
    for(int i=0; i<10; ++i) {
        v.emplace_back(i);
    }
}

class Person {
    public:
        Person(string name, int age): m_Name(name), m_Age(age) {}

        bool operator==(const Person& p) {
            if(this->m_Name == p.m_Name && this->m_Age == p.m_Age) {
                return true;
            }
            return false;
        }

        string m_Name;
        int m_Age;
};

int main(void) {
    vector<int> v;
    initVector(v);

    auto fiveIt = find(begin(v), end(v), 5);
    if(fiveIt != v.end()) {
        cout << "找到了: " << *fiveIt << endl; 
    } else {
        cout << "没有找到" << endl;
    }

    Person p1("张三", 21);
    Person p2("李四", 22);
    Person p3("王五", 23);
    Person p4("赵六", 24);

    vector<Person> vPersons;
    vPersons.emplace_back(p1);
    vPersons.emplace_back(p2);
    vPersons.emplace_back(p3);
    vPersons.emplace_back(p4);

    Person toFind("李四", 22);
    auto findIt =  find(begin(vPersons), end(vPersons), toFind);
    if(findIt != end(vPersons)) {
        cout << "找到 姓名为: " << findIt->m_Name << " 年龄为: " << findIt->m_Age << endl; 
    } else {
        cout << "查无此人" << endl;
    } 

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}