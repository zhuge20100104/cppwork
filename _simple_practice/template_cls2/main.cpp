#include <iostream>

using std::cout;
using std::endl;
#include <string>
using std::string;


template <class NameType, class AgeType>
class Person {
    public:
        Person(NameType name, AgeType age): m_Name(name), m_Age(age) {

        }

        void showPerson() const {
            cout << "姓名: " << this->m_Name << " 年龄: " << this->m_Age << endl;
        }

        NameType m_Name;
        AgeType m_Age;
};

template<class NameType, class AgeType> 
void showPersonFunc(const Person<NameType, AgeType>& p) {
    cout << "NameType: " << typeid(NameType).name() << endl;
    cout << "AgeType: " << typeid(AgeType).name() << endl;
    p.showPerson();
}

int main(void) {
    Person<string, int> p {"张三", 21};
    showPersonFunc(p); 
}