#include <memory>
#include <string>
#include <vector>
#include <cassert>

#include <boost/move/move.hpp>
#include <boost/swap.hpp>

namespace other {
    class characteristics{};
};

struct person_info {
    std::string name_;
    std::string second_name_;
    other::characteristics characteristics_;

private:
    BOOST_COPYABLE_AND_MOVABLE(person_info);
public:
    person_info();

    person_info(const person_info& p): 
        name_{p.name_},
        second_name_{p.second_name_},
        characteristics_{p.characteristics_} {}
    
    // 移动构造函数
    person_info(BOOST_RV_REF(person_info) person) {
        swap(person);
    }

    // 拷贝构造函数
    person_info& operator=(BOOST_COPY_ASSIGN_REF(person_info) person) {
        person_info tmp(person);
        swap(tmp);
        return *this;
    }
    
    // 右值移动构造函数
    person_info& operator=(BOOST_RV_REF(person_info) person) {
        person_info tmp(boost::move(person));
        swap(tmp);
        return *this;
    }
    void swap(person_info& ths);
};

void person_info::swap(person_info& ths) {
    name_.swap(ths.name_);
    second_name_.swap(ths.second_name_);
    boost::swap(characteristics_, ths.characteristics_);
}

BOOST_DEFAULTED_FUNCTION(person_info::person_info(), {})

int main(int argc, char* argv[]) {
    person_info vasya;
    vasya.name_ = "vasya";
    vasya.second_name_ = "snow";

    person_info new_vasya(boost::move(vasya));
    assert(new_vasya.name_ == "vasya");
    assert(new_vasya.second_name_ == "snow");
    assert(vasya.name_.empty());
    assert(vasya.second_name_.empty());

    vasya = boost::move(new_vasya);
    assert(vasya.name_ == "vasya");
    assert(vasya.second_name_ == "snow");
    assert(new_vasya.name_.empty());
    assert(new_vasya.second_name_.empty());

    // 拷贝赋值，两个都有值了
    new_vasya = vasya;
    assert(vasya.name_ == "vasya");
    assert(vasya.second_name_ == "snow");
    assert(new_vasya.name_ == "vasya");
    assert(new_vasya.second_name_ == "snow"); 
}
