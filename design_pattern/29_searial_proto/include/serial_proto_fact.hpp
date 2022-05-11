#ifndef _FREDRIC_SERIAL_PROTO_HPP_
#define _FREDRIC_SERIAL_PROTO_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/unique_ptr.hpp>
// 最后一个头文件必须加，支持std::unique_ptr serialization

struct Address {
    std::string street;
    std::string city;
    int suite;
    // 不加默认构造，不支持Serialization
    Address() {}

    Address(std::string const& street_,  std::string const& city_, int suite_): street{street_}, city{city_}, suite{suite_} {}

    Address(Address const& other): street{other.street}, city{other.city}, suite{other.suite}  {}

    friend std::ostream& operator<<(std::ostream& os, Address const& address) {
        return os << " street: " << address.street << " city: " << address.city << " suite: " << address.suite;  
    }

private:
    friend class boost::serialization::access;

    template <class Ar>
    void serialize(Ar& ar, unsigned int const version) {
        ar & street;
        ar & city;
        ar & suite;
    }
};

struct Contract {
    std::string name;
    std::unique_ptr<Address> address;
    // 不加默认构造，不支持Serialization
    Contract() {}

    Contract(std::string const& name_, std::unique_ptr<Address> address_): name{name_}, address{std::move(address_)} {}

    Contract(Contract const& other): name{other.name}, address{std::make_unique<Address>(*other.address)} {}

    friend std::ostream& operator<<(std::ostream& os, Contract const& contract) {
        return os << "name: " << contract.name << " address: " << *contract.address;  
    }

private:
    friend class boost::serialization::access;
    template <class Ar>
    void serialize(Ar& ar, unsigned int const version) {
        ar & name;
        ar & address;
    }
};

auto clone_ = [](Contract const& c) {
    std::ostringstream oss;
    boost::archive::text_oarchive oa {oss};
    oa << c;
    
    std::istringstream iss(oss.str());
    boost::archive::text_iarchive ia {iss};
    Contract result;
    ia >> result;
    return result;
};

#endif