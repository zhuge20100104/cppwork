#ifndef _FREDRIC_PERSON_ADDRESS_BUILDER_H_
#define _FREDRIC_PERSON_ADDRESS_BUILDER_H_

#include "person_builder.h"
#include <string>

class PersonAddressBuilder: public PersonBuilderBase {
    using Self = PersonAddressBuilder;

public:
    explicit PersonAddressBuilder(Person& person): PersonBuilderBase{person} {}

    Self& at(std::string street_address) {
        person.street_address = street_address;
        return *this;
    }

    Self& with_postcode(std::string post_code) {
        person.post_code = post_code;
        return *this;
    }

    Self& in(std::string city) {
        person.city = city;
        return *this;
    }
};

#endif