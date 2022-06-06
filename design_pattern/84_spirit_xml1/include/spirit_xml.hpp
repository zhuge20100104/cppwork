#ifndef _FREDRIC_SPIRIT_XML_HPP_
#define _FREDRIC_SPIRIT_XML_HPP_

#include <boost/config/warning_disable.hpp>
#include <boost/foreach.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace client {
namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

/**
 * @brief Mini XML Tree representation
 */
struct mini_xml;

// 要么是 mini_xml的递归结构，要么是std::string
// 这个节点的两种属性
using mini_xml_node =
    boost::variant<boost::recursive_wrapper<mini_xml>, std::string>;

struct mini_xml {
    std::string name;                     // Tag name
    std::vector<mini_xml_node> children;  // children
};
};  // namespace client

BOOST_FUSION_ADAPT_STRUCT(client::mini_xml,
                          (std::string,
                           name)(std::vector<client::mini_xml_node>, children))

namespace client {
// print out the mini xml tree
int const tabsize = 4;

void tab(int indent) {
    for (int i = 0; i < indent; ++i) {
        std::cout << ' ';
    }
}

struct mini_xml_printer {
    mini_xml_printer(int indent_ = 0) : indent{indent_} {}

    void operator()(mini_xml const& xml) const;
    int indent;
};

struct mini_xml_node_printer : boost::static_visitor<> {
    mini_xml_node_printer(int indent_ = 0) : indent{indent_} {}

    void operator()(mini_xml const& xml) const {
        mini_xml_printer(indent + tabsize)(xml);
    }

    void operator()(std::string const& text) const {
        tab(indent + tabsize);
        std::cout << "text: \"" << text << '"' << std::endl;
    }
    int indent;
};

void mini_xml_printer::operator()(mini_xml const& xml) const {
    tab(indent);
    std::cout << "tag: " << xml.name << std::endl;
    tab(indent);

    std::cout << '{' << std::endl;
    for (auto&& node : xml.children) {
        boost::apply_visitor(mini_xml_node_printer(indent), node);
    }
    tab(indent);
    std::cout << '}' << std::endl;
}

// Our mini xml grammar definition
template <typename Iterator>
struct mini_xml_grammar : qi::grammar<Iterator, mini_xml(), ascii::space_type> {

    
    mini_xml_grammar() : mini_xml_grammar::base_type(xml) {
        using ascii::char_;
        using ascii::string;
        using qi::lexeme;
        using qi::lit;
        using namespace qi::labels;

        using phoenix::at_c;
        using phoenix::push_back;

        text = lexeme[+(char_ - '<')[_val += _1]];
        node = (xml | text) [_val = _1];
        start_tag =
            '<' >> !lit('/') >> lexeme[+(char_ - '>')[_val += _1]] >> '>';

        // r1表示继承 start_tag中的属性
        end_tag = "</" >> string(_r1) >> '>';

        // 复用start_tag的内容是通过 这里实现的
        // 这里其实实现的是一个boost::fusion::tuple
        // 0 = start_tag content
        // ..... 若干 nodes
        // 最后验证end_tag == start_tag，但是不push_back
        xml = start_tag[at_c<0>(_val) = _1] >>
              *node[push_back(at_c<1>(_val), _1)] >> end_tag(at_c<0>(_val));
    }
    qi::rule<Iterator, std::string(), ascii::space_type> text;
    qi::rule<Iterator, mini_xml_node(), ascii::space_type> node;
    qi::rule<Iterator, std::string(), ascii::space_type> start_tag;
    // 继承属性，需要验证start_tag中的字符串
    qi::rule<Iterator, void(std::string), ascii::space_type> end_tag;
    qi::rule<Iterator, mini_xml(), ascii::space_type> xml;
};
};  // namespace client

#endif