#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>

#include <stdexcept>
#include <cassert>

struct datetime {
    // 时区格式类型
    enum zone_offsets_t {
        OFFSET_NOT_SET, // 未设置
        OFFSET_Z, // 0偏移
        OFFSET_UTC_PLUS, // 正偏移
        OFFSET_UTC_MINUS  // 负偏移
    };

private:
    unsigned short year_;
    unsigned short month_;
    unsigned short day_;

    unsigned short hour_;
    unsigned short minutes_;
    unsigned short seconds_;

    zone_offsets_t zone_offset_type_;
    unsigned int zone_offset_in_min_;

    static void dt_assert(bool v, const char* msg) {
        if(!v) {
            throw std::logic_error("Assertion failed in datetime: " + std::string(msg));
        }
    }

public:
    datetime():
        year_(0), month_(0), day_(0),
        hour_(0), minutes_(0), seconds_(0),
        zone_offset_type_(OFFSET_NOT_SET), zone_offset_in_min_(0)
    {}

    unsigned short year() const {
        return year_;
    }

    unsigned short month() const {
        return month_;
    }

    unsigned short day() const {
        return day_;
    }

    unsigned short hour() const {
        return hour_;
    }

    unsigned short minutes() const {
        return minutes_;
    }

    unsigned short seconds() const {
        return seconds_;
    }

    zone_offsets_t zone_offset_type() const {
        return zone_offset_type_;
    }

    unsigned int zone_offset_in_min() const {
        return zone_offset_in_min_;
    }

    void set_year(unsigned short val) {
        year_ = val;
    }

    void set_month(unsigned short val) {
        dt_assert(val > 0 && val < 13, "month parameter has incorrect value");
        month_ = val;
    }

    void set_day(unsigned short val) {
        dt_assert(val > 0 && val < 32, "day parameter has incorrect value");
        day_ = val;
    }

    void set_hour(unsigned short val) {
        dt_assert(val < 24, "hours parameter has incorrect value");
        hour_ = val;
    }

    void set_minutes(unsigned short val) {
        dt_assert(val < 60, "minutes parameter has incorrect value");
        minutes_ = val;
    }

    void set_seconds(unsigned short val) {
        dt_assert(val < 60, "seconds parameter has incorrect value");
        seconds_ = val;
    }

    void set_zone_offset_type(zone_offsets_t val) {
        zone_offset_type_ = val;
    }

    void set_zone_offset_in_min(unsigned int val) {
        zone_offset_in_min_ = val;
    }
};

void set_zone_offset(datetime& dt, char sign, unsigned short hours, unsigned short minutes) {
    dt.set_zone_offset_type(sign == '+' ? datetime::OFFSET_UTC_PLUS : datetime::OFFSET_UTC_MINUS);
    dt.set_zone_offset_in_min(hours * 60 + minutes);
}

datetime parse_date_time(const std::string& s) {
    using boost::spirit::qi::_1;
    using boost::spirit::qi::_2;
    using boost::spirit::qi::_3;
    using boost::spirit::qi::uint_parser;
    using boost::spirit::qi::char_;
    using boost::phoenix::bind;
    using boost::phoenix::ref;

    datetime ret;
    uint_parser<unsigned short, 10, 2, 2> u2_;
    uint_parser<unsigned short, 10, 4, 4> u4_;

    // -号表示可选规则, 时区配置规则
    boost::spirit::qi::rule<const char*, void()> timezone_parser =
        -(
            char_('Z') [bind(&datetime::set_zone_offset_type, &ret, datetime::OFFSET_Z)]
            | 
            ((char_('+')|char_('-')) >> u2_ >> ':' >> u2_) [ bind(&set_zone_offset, ref(ret), _1, _2, _3) ]
        );
    
    // 日期配置规则
    boost::spirit::qi::rule<const char*, void()> date_parser = 
        u4_[ bind(&datetime::set_year, &ret, _1) ] >> char_('-')
        >> u2_[ bind(&datetime::set_month, &ret, _1) ] >> char_('-')
        >> u2_[ bind(&datetime::set_day, &ret, _1) ];
    
    // 时间配置规则
    boost::spirit::qi::rule<const char*, void()> time_parser = 
        u2_ [ bind(&datetime::set_hour, &ret, _1) ] >> char_(':')
        >> u2_[ bind(&datetime::set_minutes, &ret, _1) ] >> char_(':')
        >> u2_[ bind(&datetime::set_seconds, &ret, _1) ];

    const char* first = s.data();
    const char* const end = first + s.size();
    bool success = boost::spirit::qi::parse(first, end,
        ((date_parser >> char_('T') >> time_parser) | date_parser | time_parser)
        >> timezone_parser
    );

    if(!success || first != end) {
        throw std::logic_error("Parsing of '" + s + "' failed");
    }
    return ret;
}

int main(int argc, char* argv[]) {
    datetime d1 = parse_date_time("2012-10-20T10:00:00Z");
    assert(d1.year() == 2012);
    assert(d1.month() == 10);
    assert(d1.day() == 20);
    assert(d1.hour() == 10);
    assert(d1.minutes() == 0);
    assert(d1.seconds() == 0);
    assert(d1.zone_offset_type() == datetime::OFFSET_Z);
    assert(d1.zone_offset_in_min() == 0);

    datetime d2 = parse_date_time("2012-10-20T10:00:00");
    assert(d2.year() == 2012);
    assert(d2.month() == 10);
    assert(d2.day() == 20);
    assert(d2.hour() == 10);
    assert(d2.minutes() == 0);
    assert(d2.seconds() == 0);
    assert(d2.zone_offset_type() == datetime::OFFSET_NOT_SET);
    assert(d2.zone_offset_in_min() == 0);

    datetime d3 = parse_date_time("2012-10-20T10:00:00+09:15");
    assert(d3.year() == 2012);
    assert(d3.month() == 10);
    assert(d3.day() == 20);
    assert(d3.hour() == 10);
    assert(d3.minutes() == 0);
    assert(d3.seconds() == 0);
    assert(d3.zone_offset_type() == datetime::OFFSET_UTC_PLUS);
    assert(d3.zone_offset_in_min() == 9 * 60 + 15);
}