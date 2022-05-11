#include <boost/lexical_cast.hpp>
#include <boost/array.hpp>

#include <iostream>
#include <stdexcept>

#include <cassert>

class negative_number {
    unsigned short number_;

public:
    explicit negative_number(unsigned short number = 0): number_(number) 
    {}

    unsigned short value_without_sign() const {
        return number_;
    }
};

// 为窄字符版本重载输入输出操作符
std::ostream& operator<< (std::ostream& os, const negative_number& number) {
    os << '-' << number.value_without_sign();
    return os;
}

std::istream& operator>> (std::istream& is, negative_number& number) {
    char ch;
    is >> ch;
    if(ch != '-') {
        throw std::logic_error("Negative_number class designed to store only negative values");
    }

    unsigned short s;
    is >> s;
    number = negative_number(s);
    return is;
}

// 为宽字符版本重载输入输出操作符
template <class charT>
std::basic_ostream<charT>& operator<< (std::basic_ostream<charT>& os, const negative_number& number) {
    os << static_cast<charT>('-') << number.value_without_sign();
    return os;
}

template <class charT>
std::basic_istream<charT>& operator>> (std::basic_istream<charT>& is, negative_number& number) {
    charT ch;
    is >> ch;
    if(ch != static_cast<charT>('-')) {
        throw std::logic_error("Negative_number class designed to store only negative numbers");
    }
    unsigned short s;
    is >> s;
    number = negative_number(s);
    return is;
} 

void foo1() {
    negative_number n = boost::lexical_cast<negative_number>("-100");
    assert(n.value_without_sign() == 100);

    int i = boost::lexical_cast<int>(n);
    assert(i == -100);

    using arr_t = boost::array<char, 10>;
    arr_t arr = boost::lexical_cast<arr_t>(n);
    assert(arr[0] == '-');
    assert(arr[1] == '1');
    assert(arr[2] == '0');
    assert(arr[3] == '0');
    assert(arr[4] == '\0');
}

void foo2() {
    negative_number n = boost::lexical_cast<negative_number>(L"-1");
    assert(n.value_without_sign() == 1);

    using warr_t = boost::array<wchar_t, 10>;
    warr_t arr = boost::lexical_cast<warr_t>(n);
    assert(arr[0] == L'-');
    assert(arr[1] == L'1');
    assert(arr[2] == L'\0');
}

int main(int argc, char* argv[]) {
    foo1();
    foo2();
}