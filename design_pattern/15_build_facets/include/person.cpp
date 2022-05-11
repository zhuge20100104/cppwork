#include "person.h"
#include "person_builder.h"

PersonBuilder Person::create() {
    return PersonBuilder{};
}