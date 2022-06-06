#ifndef _PERSON_H_
#define _PERSON_H_

class Person{
    public:
        Person();
        int mA;
        int mB;
        Person operator+(Person& other);
};
#endif
