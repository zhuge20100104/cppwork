#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>
using std::string;

class Person {
    public:
        Person(string name, int score):m_Name(name), m_Score(score) {}
        string m_Name;
        int m_Score;
};
#endif