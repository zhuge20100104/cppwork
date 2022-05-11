#include "person.h"



Person::Person():mA(0), mB(0) {
}

Person Person::operator+(Person& other) {
    Person tmp;
    tmp.mA = this->mA + other.mA;
    tmp.mB = this->mB + other.mB;
    return tmp;
}


