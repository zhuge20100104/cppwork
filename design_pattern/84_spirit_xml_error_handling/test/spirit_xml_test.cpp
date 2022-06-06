#include "spirit_xml_error_hand.hpp"

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <fstream>

#include "death_handler/death_handler.h"

int main(int argc, char** argv) {
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;

    Debug::DeathHandler dh;

    google::InitGoogleLogging("./logs.log");
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

bool parse_xml(char const* filename) {
    std::ifstream in{filename, std::ios_base::in};
    if (!in) {
        std::cerr << "Error: could not open input file: " << filename
                  << std::endl;
        return false;
    }
    // We will read the contents here
    std::string storage;
    // Do not skip whitespace
    in.unsetf(std::ios::skipws);
    std::copy(std::istream_iterator<char>(in), std::istream_iterator<char>(),
              std::back_inserter(storage));

    namespace qi = boost::spirit::qi;
    using iterator_type = std::string::const_iterator;
    using mini_xml_grammar = client::mini_xml_grammar<iterator_type>;
    using boost::spirit::ascii::space;

    // Our grammar
    mini_xml_grammar xml;
    // Our tree
    client::mini_xml ast;
    iterator_type iter = storage.begin();
    iterator_type end = storage.end();

    bool r = qi::phrase_parse(iter, end, xml, space, ast);
    if (r && iter == end) {
        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded\n";
        client::mini_xml_printer printer;
        printer(ast);
        std::cout << "-------------------------\n";
        return true;
    } else {
        std::string rest{iter, end};
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "Stopped at: \"" << rest << "\"\n";
        std::cout << "-------------------------\n";
        return false;
    }
}

GTEST_TEST(SpiritXMLTests, SpiritXML) {
    parse_xml("../data/1.xml");
}

GTEST_TEST(SpiritXMLTests, SpiritXMLError) {
    parse_xml("../data/2.xml");
}