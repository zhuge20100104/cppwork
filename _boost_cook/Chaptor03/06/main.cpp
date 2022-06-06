#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi.hpp>

#include <cassert>

struct date {
    unsigned short year;
    unsigned short month;
    unsigned short day;
};

date parse_date_time1(const std::string& s) {
    using boost::spirit::qi::_1;
    using boost::spirit::qi::ushort_;
    using boost::spirit::qi::char_;
    using boost::phoenix::ref;

    date res;
    const char* first = s.data();
    const char* const end = first + s.size();

    bool success = boost::spirit::qi::parse(first, end, 
        ushort_[ ref(res.year) = _1 ] >> char_('-') >> ushort_[ ref(res.month) = _1 ]
        >> char_('-') >> ushort_[ ref(res.day) = _1 ]
    );

    if(!success || first != end) {
        throw std::logic_error("Parsing failed");
    }
    return res;
}

date parse_date_time2(const std::string& s) {
    using boost::spirit::qi::_1;
    using boost::spirit::qi::uint_parser;
    using boost::spirit::qi::char_;
    using boost::phoenix::ref;
    // 表示两位十进制数
    uint_parser<unsigned short, 10, 2, 2> u2;
    // 表示四位十进制数
    uint_parser<unsigned short, 10, 4, 4> u4;

    date res;
    const char* first = s.data();
    const char* const end = first + s.size();

    bool success = boost::spirit::qi::parse(first, end, 
        u4[ ref(res.year) == _1 ] >> char_('-') >> u2[ ref(res.month) = _1 ]
        >> char_('-') >> u2[ ref(res.day) = _1 ]
    );
    if(!success || first != end) {
        throw std::logic_error("Parsing failed");
    }
    return res;
}

int main(int argc, char* argv[]) {
    date d = parse_date_time1("2012-12-31");
    assert(d.year == 2012);
    assert(d.month == 12);
    assert(d.day == 31);

    date d2 = parse_date_time2("2012-12-31");
    assert(d2.year == 2012);
    assert(d2.month == 12);
    assert(d2.day == 31);

    try {
        parse_date_time2("12345-12-31");
        assert(false);
    }catch(const std::logic_error& e) {
        std::cerr << "Parse failed, reason: " <<  e.what() << std::endl;
    }
}