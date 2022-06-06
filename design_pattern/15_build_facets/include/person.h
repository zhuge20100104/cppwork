#ifndef _FREDRIC_PERSON_H_
#define _FREDRIC_PERSON_H_

#include <string>
#include <iostream>

class PersonBuilder;

class Person {
    // Address
    std::string street_address, post_code, city;

    // Employeement 
    std::string company_name, position;
    int annual_come = 0;

    Person() {
        std::cout << "Person created\n";
    }

public:
    ~Person() {
        std::cout << "Person destroyed\n";
    }

    static PersonBuilder create();

    Person(Person&& other): street_address(std::move(other.street_address)), post_code(std::move(other.post_code)),
    city(std::move(other.city)), company_name(std::move(other.company_name)), position(std::move(other.position)), annual_come(other.annual_come) {

    }

    Person& operator=(Person&& other) {
        if(this == &other) {
            return *this;
        }

        street_address = std::move(other.street_address);
        post_code = std::move(other.post_code);
        city = std::move(other.city);
        company_name = std::move(other.company_name);
        position = std::move(other.position);
        annual_come = other.annual_come;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, Person const& obj) {
        return os 
            << "street_address: " << obj.street_address
            << " post_code: " << obj.post_code
            << " city: " << obj.city
            << " company_name: " << obj.company_name
            << " position: " << obj.position
            << " annual_come: " << obj.annual_come;
    }

    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;
};
#endif