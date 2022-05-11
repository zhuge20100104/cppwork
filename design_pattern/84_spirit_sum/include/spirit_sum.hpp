#ifndef _FREDRIC_SPIRIT_SUM_HPP_
#define _FREDRIC_SPIRIT_SUM_HPP_

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace client {
    template <typename Iterator>
    bool adder(Iterator first, Iterator last, double& n) {
        using boost::spirit::qi::double_;
        using boost::spirit::qi::_1;
        using boost::spirit::qi::phrase_parse;
        using boost::spirit::ascii::space;
        using boost::phoenix::ref;

        // 第一个数直接赋值，后面的数  += 值
        bool r = phrase_parse(first,
            last,
            // Begin Grammer
            (
                double_[ref(n)=_1] >> *(',' >> double_[ref(n)+=_1])
            ),
            // End Grammer
            space);
        if(!r || first != last) { // failed if we didn't get a full match
            return false;
        }
        return r;
    }
};


#endif