#ifndef _FREDRIC_SPIRIT_NUM_LIST1_HPP_
#define _FREDRIC_SPIRIT_NUM_LIST1_HPP_

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace client {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    
    template <typename Iterator>
    bool parse_numbers(Iterator first, Iterator last) {
        using qi::double_;
        using qi::phrase_parse;
        using ascii::space;
        bool r = phrase_parse(first,
            last,
            // Start expression
            double_ >> *(',' >> double_), // double,double,double,double
            // End expression
            space
            );
        if(first != last) { // failed if we didn't get a full match
            return false;
        }

        return r;
    }
};
#endif