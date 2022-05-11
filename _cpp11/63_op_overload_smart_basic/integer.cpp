#include "integer.h"
#include <iostream>

Integer::Integer() {
    std::cout << "Integer::Integer()\n";
    m_pint = new int(0);
}
Integer::Integer(int value) {
    std::cout << "Integer::Integer(int value)\n";
    m_pint = new int(value);
}

Integer::Integer(Integer const& obj) {
    std::cout << "Integer::Integer(Integer const& obj)\n";
    // 不能自己给自己赋值
    if(this == &obj) {
        return;
    }
    m_pint = new int(obj.get_value());
}

Integer& Integer::operator=(Integer const& obj) {
    std::cout << "Integer::operator=(Integer const& obj)\n";
    if(this == &obj) {
        return *this;
    }

    delete m_pint;
    m_pint = new int(obj.get_value());
    return *this;
}

Integer& Integer::operator=(Integer&& obj) {
    std::cout << "Integer::operator=(Integer&& obj)\n";
    if(this == &obj) {
        return *this;
    }
    delete m_pint;
    m_pint = obj.m_pint;
    obj.m_pint = nullptr;
    return *this;
}

Integer Integer::operator+(Integer const& a) const {
    Integer temp;
    *temp.m_pint = *(this->m_pint) + *(a.m_pint);
    return temp;
}

Integer& Integer::operator++() {
    ++*(this->m_pint);
    return *this;
}

Integer Integer::operator++(int) {
     Integer temp{*this};
     ++(*this->m_pint);
     return temp;
}

bool Integer::operator==(Integer const& other) {
    return *(this->m_pint) == *(other.m_pint);
}


Integer::Integer(Integer&& obj) {
    std::cout << "Integer::Integer(Integer&& obj)\n";
    if(this == &obj) {
        return;
    }
    m_pint = obj.m_pint;
    obj.m_pint = nullptr;
}

int Integer::get_value() const {
    return *m_pint;
}

void Integer::set_value(int value) {
    // 移动构造后能够重新赋值
    if(m_pint == nullptr) {
        m_pint = new int{};
    }
    *m_pint = value;
}

Integer::~Integer() {
    std::cout << "Integer::~Integer()\n";
    if(nullptr != m_pint) {
        delete m_pint;
        m_pint = nullptr;
    }
}