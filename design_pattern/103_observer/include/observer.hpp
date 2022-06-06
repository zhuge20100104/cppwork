#ifndef _FREDRIC_OBSERVER_HPP_
#define _FREDRIC_OBSERVER_HPP_

#include "observerable.hpp"

#include <string>
#include <iostream>

template <typename T>
struct Observer {
    virtual void field_changed(
        T& source,   // reference to the object that changed
        std::string const& field_name   // name of field(property) that changed
    ) = 0;
};


class Person: public Observerable<Person> { // Observable 
    int age;
public:
    Person(int age_): age{age_} {}
    int get_age() const {
        return age;
    }    

    void set_age(int age_) {
        if(this->age == age_) return;
        this->age = age_;
        notify(*this, "age");
    } 
};

struct ConsolePersonObserver: Observer<Person> {
    void field_changed(Person& source, std::string const& field_name) override {
        std::cout << "Person's " << field_name << " has changed to ";
        if(field_name == "age") {
            std::cout << source.get_age();
        }
        std::cout << "\n";
    }
};

#endif