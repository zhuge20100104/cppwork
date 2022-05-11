#include "person_impl.h"

#include <iostream>

class Person::PersonImpl {
public:
    void greet(Person* p);
};

void Person::PersonImpl::greet(Person* p) {
    std::cout << "Hello, my name is: " << p->name << "\n";
}

Person::Person(std::string const& name_): name{name_}, impl{new PersonImpl{}} {
}

void Person::greet() {
    impl->greet(this);
}

Person::~Person() {
    delete impl;
}