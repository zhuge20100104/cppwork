// 包含 boost::iequals 忽略大小写比较
#include <boost/algorithm/string/predicate.hpp>
// 包含 boost::is_iequal 忽略大小写比较单个字符是否相当的函数
#include <boost/algorithm/string/compare.hpp>
// 包含大小写转换的相关函数
#include <boost/algorithm/string/case_conv.hpp>

#include <algorithm>

std::string str1 = "Thanks for reading me!";
std::string str2 = "Thanks for reading ME!";

void method1() {
    // 忽略大小写， str1 == str2
    assert(boost::iequals(str1, str2));
}

void method2() {
    assert(str1.size() == str2.size() &&
        std::equal(str1.begin(), str1.end(),
        str2.begin(), boost::is_iequal())
    );
}

void method3() {
    // 不修改原始字符串，转换成小写比较
    std::string str1_low = boost::to_lower_copy(str1);
    std::string str2_low = boost::to_lower_copy(str2);
    assert(str1_low == str2_low);
}

void method4() {
    // 不修改原始字符串，转换成大写比较
    std::string str1_up = boost::to_upper_copy(str1);
    std::string str2_up = boost::to_upper_copy(str2);
    assert(str1_up == str2_up);
}

void method5() {
    // 直接修改原始字符串到小写，然后比较
    boost::to_lower(str1);
    boost::to_lower(str2);
    assert(str1 == str2);
}

int main(int argc, char* argv[]) {
    method1();
    method2();
    method3();
    method4();
    method5();

    // 在某些平台上std::locale::classic比std::locale()要快
    boost::iequals(str1, str2, std::locale::classic());
}
