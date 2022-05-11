#ifndef _FREDRIC_PERSON1_H_
#define _FREDRIC_PERSON1_H_

#include "pimpl.hpp"

#include <string>

class Person {
public:
    class PersonImpl;
    PImpl<PersonImpl> impl_;

    std::string name;
    Person(std::string const& name_);
    // 这个析构函数必须，否则可能会导致编译器找不到PersonImpl的大小
    // 无法工作
    ~Person();
    void greet();
};
#endif