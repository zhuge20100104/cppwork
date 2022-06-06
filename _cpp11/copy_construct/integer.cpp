#include "integer.h"

Integer::Integer() {
    m_pInt = new int(0);
}

Integer::Integer(int value) {
    m_pInt = new int(value);
}

int Integer::get_value() const {
    return *m_pInt;
}

void Integer::set_value(int value) {
    *m_pInt = value;
}

Integer::Integer(Integer const& rhs) {
    m_pInt = new int(rhs.get_value());
}

Integer& Integer::operator=(Integer const& rhs) {
    if(this == &rhs) {
        return *this;
    }
    if(m_pInt != nullptr) {
        delete m_pInt;
    }

    m_pInt = new int(rhs.get_value());
    return *this;
}

Integer::Integer(Integer&& rhs) {
    m_pInt = rhs.m_pInt;
    rhs.m_pInt = nullptr;
}

Integer& Integer::operator=(Integer&& rhs) {
    if(this == &rhs) {
        return *this;
    }
    m_pInt = rhs.m_pInt;
    rhs.m_pInt = nullptr;
    return *this;
}

Integer::~Integer() {
    delete m_pInt;
    m_pInt = nullptr;
}