#ifndef _FREDRIC_PROB_OF_DEPS_HPP_
#define _FREDRIC_PROB_OF_DEPS_HPP_

#include <boost/signals2.hpp>

#include <string>
#include <iostream>

namespace sig = boost::signals2;

template <typename T>
struct Observerable {
    virtual ~Observerable() = default;
    // 观察者就是这个signal，一旦发生改变，就触发观察者的事件
    sig::signal<void(T&, std::string const&)> property_changed;
};


class Person: public Observerable<Person> { // Observable 
    int age;
public:
    explicit Person(int age_): age{age_} {
        property_changed.connect([](Person&, std::string const& prop_name){
            std::cout << prop_name << " has been changed" << std::endl;
        });
    }

    int get_age() const {
        return age;
    }    

    bool get_can_vote() const {
        return age >= 16;
    }

    void set_age(int age_) {
        if(this->age == age_) return;

        auto old_can_vote = this->get_can_vote();
        this->age = age_;
        property_changed(*this, "age");

        if(old_can_vote != get_can_vote()) {
            property_changed(*this, "can_vote");
        }
    } 
};


#endif