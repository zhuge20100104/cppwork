#ifndef _FREDRIC_CONTRACT_HPP_
#define _FREDRIC_CONTRACT_HPP_

#include <string>

struct Address {
    std::string street;
    std::string city;
    int suite;

    Address(std::string const& street_,  std::string const& city_, int suite_): street{street_}, city{city_}, suite{suite_} {}

    friend std::ostream& operator<<(std::ostream& os, Address const& address) {
        return os << " street: " << address.street << " city: " << address.city << " suite: " << address.suite;  
    }
};

struct Contract {
    std::string name;
    Address address;

    Contract(std::string const& name_, Address const& address_): name{name_}, address{address_} {}

    friend std::ostream& operator<<(std::ostream& os, Contract const& contract) {
        return os << "name: " << contract.name << " address: " << contract.address;  
    }
};
#endif