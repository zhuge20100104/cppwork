#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
using std::string;

class Person {
    public:
        Person(string name, int age);
        bool operator==(const Person& other);
    private:
        string mName;
        int mAge;
};
#endif
