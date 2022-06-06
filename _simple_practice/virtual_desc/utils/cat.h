#ifndef _CAT_H_
#define _CAT_H_

#include "animal.h"
#include <memory>
#include <string>
using std::string;

using strPtr = std::shared_ptr<string>;

class Cat: public Animal{
    public:
        Cat(string name): m_Name(new string(name)) {

        }

        virtual void Speak();

        virtual ~Cat() {
            cout << "cat类的析构函数被调用" << endl;
        }
    private:
        strPtr m_Name;
};

void Cat::Speak() {
    cout << *m_Name << "小猫正在说话" << endl;
}

#endif