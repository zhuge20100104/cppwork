#include "person.h"

Person::Person(string name, int age): mName(name), mAge(age){
    
}


bool Person::operator==(const Person& other) {
    if(this->mName == other.mName && this->mAge == other.mAge) {
        return true;
    }
    return false;
}
