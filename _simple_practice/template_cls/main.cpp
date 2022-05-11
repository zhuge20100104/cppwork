#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

#include <cstdlib>

template <class NameType, class AgeType>
class Person {
    public:
        Person(NameType _name, AgeType _age): name(_name), age(_age) {}

        NameType name;
        AgeType age;
        void showPerson() {
            cout << "name: " << name << " age: " << age << endl;
        }
};


int main(void) {

    Person<string, int> p {"张三", 20};
    p.showPerson();

    Person<const char*, int> p1 {"李四", 23};
    p1.showPerson();

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}