#ifndef _FREDRIC_CONTRACT_PROTO_HPP_
#define _FREDRIC_CONTRACT_PROTO_HPP_

#include <string>
#include <iostream>
#include <memory>

struct Address {
    std::string street;
    std::string city;
    int suite;

    Address(std::string const& street_,  std::string const& city_, int suite_): street{street_}, city{city_}, suite{suite_} {}

    Address(Address const& other): street{other.street}, city{other.city}, suite{other.suite}  {}

    friend std::ostream& operator<<(std::ostream& os, Address const& address) {
        return os << " street: " << address.street << " city: " << address.city << " suite: " << address.suite;  
    }
};

struct Contract {
    std::string name;
    std::unique_ptr<Address> address;

    Contract(std::string const& name_, std::unique_ptr<Address> address_): name{name_}, address{std::move(address_)} {}

    Contract(Contract const& other): name{other.name}, address{std::make_unique<Address>(*other.address)} {}

    friend std::ostream& operator<<(std::ostream& os, Contract const& contract) {
        return os << "name: " << contract.name << " address: " << *contract.address;  
    }
};
#endif