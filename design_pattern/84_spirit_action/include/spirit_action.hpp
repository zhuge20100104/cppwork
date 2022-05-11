#ifndef _FREDRIC_SPIRIT_ACTION_HPP_
#define _FREDRIC_SPIRIT_ACTION_HPP_

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace client {
    namespace qi = boost::spirit::qi;

    // A plain function
    void print(int const& i) {
        std::cout << i << std::endl;
    }

    // A member function
    struct writer {
        void print(int const& i) const {
            std::cout << i << std::endl;
        }
    };

    // A function object
    struct print_action {
        void operator()(int const& i, qi::unused_type, qi::unused_type) const {
            std::cout << i << std::endl;
        }
    };
};


#endif