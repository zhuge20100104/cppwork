#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
using std::count;
#include <cstdlib>
#include <string>
using std::string;
#include <vector>
using std::vector;
using std::begin;
using std::end;

class Person {
    public:
        Person(string name, int age): m_Name(name), m_Age(age) {}

        bool operator==(const Person& p) {
            if(this->m_Age == p.m_Age) {
                return true;
            }
            return false;
        }

        string m_Name;
        int m_Age;
};

int main(void) {

    Person p1("张三", 23);
    Person p2("李四", 23);
    Person p3("王五", 24);
    Person p4("赵六", 25);
    Person p5("李七", 26);

    vector<Person> v;
    v.emplace_back(p1);
    v.emplace_back(p2);
    v.emplace_back(p3);
    v.emplace_back(p4);
    v.emplace_back(p5);

    Person zhuge("诸葛亮", 23);

    auto countVal = count(begin(v), end(v), zhuge);

    cout << "和 [诸葛亮] 同岁的人员个数为: " << countVal << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
