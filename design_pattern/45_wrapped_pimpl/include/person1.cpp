#include "person1.h"

#include <iostream>

class Person::PersonImpl{
public:
    void greet(Person* p);
};

void Person::PersonImpl::greet(Person* p) {
    std::cout << "Hello, my name is: " << p->name << "\n";
}

Person::Person(std::string const& name_): name{name_}, impl_(){
}

void Person::greet() {
    impl_->greet(this);
}

Person::~Person() {
    
}
