#ifndef _FREDRIC_PERSON_H_
#define _FREDRIC_PERSON_H_

#include <string>

class Person {
    class PersonImpl;
    PersonImpl* impl;
public:
    std::string name;

    Person(std::string const& name_);
    ~Person();

    void greet();
};
#endif