#ifndef _FREDRIC_CONTRACT_PROTO_HPP_
#define _FREDRIC_CONTRACT_PROTO_HPP_

#include <string>
#include <iostream>
#include <memory>

struct Address {
    std::string street;
    std::string city;
    int suite;

    Address() {}

    Address(std::string const& street_,  std::string const& city_, int suite_): street{street_}, city{city_}, suite{suite_} {}

    Address(Address const& other): street{other.street}, city{other.city}, suite{other.suite}  {}

    friend std::ostream& operator<<(std::ostream& os, Address const& address) {
        return os << " street: " << address.street << " city: " << address.city << " suite: " << address.suite;  
    }
};

struct Contract {
    std::string name;
    std::unique_ptr<Address> address;

    Contract() {}
     
    Contract(std::string const& name_, std::unique_ptr<Address> address_): name{name_}, address{std::move(address_)} {}

    Contract(Contract const& other): name{other.name}, address{std::make_unique<Address>(*other.address)} {}

    friend std::ostream& operator<<(std::ostream& os, Contract const& contract) {
        return os << "name: " << contract.name << " address: " << *contract.address;  
    }
};

struct EmployeeFactory {
    static std::unique_ptr<Contract> new_main_office_employee(std::string const& name, int const suite) {
        // 在栈上全局构造Contract对象
        static Contract p {"", std::make_unique<Address>("123 East Dr", "London", 0)};
        return new_employee(name, suite, p);
    }
private:
    static std::unique_ptr<Contract> new_employee(std::string const& name, int const suite, Contract const& p) {
        auto result = std::make_unique<Contract>(p);
        result->name = name;
        result->address->suite = suite;
        return result;
    }

};
#endif