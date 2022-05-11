#ifndef _FREDRIC_SPIRIT_EMP_STRUCT_HPP_
#define _FREDRIC_SPIRIT_EMP_STRUCT_HPP_

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace client {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    struct employee {
        int age;
        std::string surname;
        std::string forename;
        double salary;
    };
};

// 注册 employee 到boost::fusion名称空间
BOOST_FUSION_ADAPT_STRUCT(
    client::employee,
    (int, age)
    (std::string, surname)
    (std::string, forename)
    (double, salary)
)

namespace client {
    // employee 解析语法
    template <typename Iterator>
    struct employee_parser: qi::grammar<Iterator, employee(), ascii::space_type> {
        employee_parser(): employee_parser::base_type(start) {
            using qi::int_;
            using qi::lit;
            using qi::double_;
            using qi::lexeme;
            using ascii::char_;
            // lexme不允许跳过空格
            quoted_string %= lexeme['"' >> +(char_ - '"') >> '"'];
            start %= lit("employee")
                    >> '{'
                    >> int_ >> ','
                    >> quoted_string >> ','
                    >> quoted_string >> ','
                    >> double_
                    >> '}';
        }
        qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
        qi::rule<Iterator, employee(), ascii::space_type> start;
    };
};
#endif