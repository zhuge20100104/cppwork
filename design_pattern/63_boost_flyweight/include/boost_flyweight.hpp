#ifndef _FREDRIC_HMADE_FLYWEIGHT_HPP_
#define _FREDRIC_HMADE_FLYWEIGHT_HPP_

#include <string>
#include <iostream>
#include <boost/flyweight.hpp>

struct User {
    boost::flyweight<std::string> first_name, last_name;

    User(std::string const& first_name_, std::string const& last_name_): first_name{first_name_}, last_name{last_name_} {
    }

    friend std::ostream& operator<<(std::ostream& os, User const& user) {
        os << "first name: " << user.first_name <<
            " last name: " << user.last_name;
        return os;
    }
};


#endif