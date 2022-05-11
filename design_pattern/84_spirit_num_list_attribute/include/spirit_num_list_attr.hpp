#ifndef _FREDRIC_SPIRIT_NUM_LIST_ATTR_HPP_
#define _FREDRIC_SPIRIT_NUM_LIST_ATTR_HPP_

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace client {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;
    
    template <typename Iterator>
    bool parse_numbers(Iterator first, Iterator last, std::vector<double>& v) {
        using qi::double_;
        using qi::phrase_parse;
        using qi::_1;
        using ascii::space;
        using phoenix::push_back;

        // 这里std::vector当做属性传入
        // 所有元素都放到vector里面返回
        bool r = phrase_parse(first,
            last,
            // Start expression
            (double_ % ','),
            // End expression
            space,
            v);
        if(first != last) { // failed if we didn't get a full match
            return false;
        }

        return r;
    }
};
#endif