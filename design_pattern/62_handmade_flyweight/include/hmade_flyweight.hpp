#ifndef _FREDRIC_HMADE_FLYWEIGHT_HPP_
#define _FREDRIC_HMADE_FLYWEIGHT_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <boost/bimap.hpp>

using key = uint32_t;

struct User {
    User(std::string const& first_name_, std::string const& last_name_): first_name{add(first_name_)}, last_name{add(last_name_)} {

    }
    // 根据key找value
    std::string const& get_first_name() const {
        return names.left.find(first_name)->second;
    }

    std::string const& get_last_name() const {
        return names.left.find(last_name)->second;
    }

    friend std::ostream& operator<<(std::ostream& os, User const &user) {
        os << "first name: " << user.get_first_name() << " last name: " << user.get_last_name() << " last name index: " << user.last_name;
        return os;
    }
protected:
    key first_name, last_name;
    static boost::bimap<key, std::string> names;
    static key seed;
    static key add(std::string const& s) {
        auto it = names.right.find(s);
        // 在names中没找着，直接插
        if(it == names.right.end()) {
            key id = ++seed;
            names.insert({id, s});
            return id;
        }
        // 找到了，直接返回key
        return it->second;
    }
};


boost::bimap<key, std::string> User::names{};
key User::seed{0};

#endif