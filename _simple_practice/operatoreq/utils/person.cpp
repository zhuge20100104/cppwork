#include "person.h"


Person::Person(int age) {
    this->mAge = new int(age);
    cout << "Person类带参数构造函数调用..." << endl;
}

Person::Person(const Person& p){
    this->mAge = new int(*p.mAge);
    cout << "Person 类拷贝构造函数调用..." << endl;
}

Person& Person::operator=(Person& p) {
    if(this->mAge != NULL) {
        delete this->mAge;
        this->mAge = NULL;
    }

    this->mAge = new int(*p.mAge);
    cout << "赋值操作符被调用..." << endl;
    return *this;
}

Person::~Person() {
    if(this->mAge != NULL) {
        delete this->mAge;
        this->mAge = NULL;
    }
}
