#ifndef _FREDRIC_PERSON_JOB_BUILDER_H_
#define _FREDRIC_PERSON_JOB_BUILDER_H_

#include "person_builder.h"
#include <string>

class PersonJobBuilder: public PersonBuilderBase {
    using Self = PersonJobBuilder;

public:
    explicit PersonJobBuilder(Person& person): PersonBuilderBase{person} {}

    Self& at(std::string company_name) {
        person.company_name = company_name;
        return *this;
    }

    Self& as_a(std::string position) {
        person.position = position;
        return *this;
    }

    Self& earning(int annual_come) {
        person.annual_come = annual_come;
        return *this;
    }
};

#endif