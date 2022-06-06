#ifndef _FREDRIC_SPIRIT_COMPLEX_HPP_
#define _FREDRIC_SPIRIT_COMPLEX_HPP_

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <complex>

namespace client {
    template <typename Iterator>
    bool parse_complex(Iterator first, Iterator last, std::complex<double>& c) {
        using boost::spirit::qi::double_;
        using boost::spirit::qi::_1;
        using boost::spirit::qi::phrase_parse;
        using boost::spirit::ascii::space;
        using boost::phoenix::ref;

        double rN = 0.0;
        double iN = 0.0;

        // -p出现0或1次
        // 接收两种情况
        // (a, b) = a + b*i
        // a = a
        bool r = phrase_parse(first,
            last,
            // Begin Grammer
            (
                '(' >> double_[ref(rN)=_1]
                    >> -(',' >> double_[ref(iN)=_1])
                  >> ')' | 
                  double_[ref(rN)=_1]
            ),
            // End Grammer
            space);
        if(!r || first != last) { // failed if we didn't get a full match
            return false;
        }
        c = std::complex<double>(rN, iN);
        return r;
    }
};


#endif