#ifndef _FREDRIC_SPIRIT_ROMAN_HPP_
#define _FREDRIC_SPIRIT_ROMAN_HPP_

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
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    // 百位数 规则 符号表
    struct hundreds_: qi::symbols<char, unsigned> {

        hundreds_() {
            add("C", 100)
            ("CC", 200)
            ("CCC", 300)
            ("CD", 400)
            ("D", 500)
            ("DC", 600)
            ("DCC", 700)
            ("DCCC", 800)
            ("CM", 900);
        }
       
    } hundreds;

    struct tens_: qi::symbols<char, unsigned>{
        tens_() {
            add("X", 10)
            ("XX", 20)
            ("XXX", 30)
            ("XL", 40)
            ("L", 50)
            ("LX", 60)
            ("LXX", 70)
            ("LXXX", 80)
            ("XC", 90);
        }
    } tens;

    struct ones_: qi::symbols<char, unsigned> {
        ones_() {
            add("I", 1)
            ("II", 2)
            ("III", 3)
            ("IV", 4)
            ("V", 5)
            ("VI", 6)
            ("VII", 7)
            ("VIII", 8)
            ("IX", 9);
        }
    } ones;

    template <typename Iterator>
    struct roman: qi::grammar<Iterator, unsigned()> {
        roman(): roman::base_type(start) {
            using qi::eps;
            using qi::lit;
            using qi::_val;
            using qi::_1;
            using ascii::char_;
            // eps 永远成功，表示在任意事情之前，先将_val赋值为0
            start = eps [_val = 0] >> (
                +lit('M') [_val += 1000]
                || hundreds [_val += _1]
                || tens [_val += _1]
                || ones [_val += _1]
            );
        }
        qi::rule<Iterator, unsigned()> start;
    }; 
};
#endif