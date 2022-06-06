#ifndef _FREDRIC_PERSON_BUILDER_H_
#define _FREDRIC_PERSON_BUILDER_H_
#include "person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase {
protected:
    Person& person;

    explicit PersonBuilderBase(Person& p): person{p} {
    }

public:
    operator Person() const {
        return std::move(person);
    }

    // builder facets
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;

};

class PersonBuilder: public PersonBuilderBase {
    Person p;
public:
    PersonBuilder(): PersonBuilderBase{p} {}
};
#endif