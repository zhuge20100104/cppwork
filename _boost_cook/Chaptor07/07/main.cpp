#include <boost/utility/string_ref.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/lexical_cast.hpp>

#include <iterator>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include <cassert>

std::string between_str(const std::string& input, char starts, char ends) {
    auto pos_beg = std::find(input.begin(), input.end(), starts);
    if(pos_beg == input.end()) {
        return std::string();
    }
    // 起始字符串位置加1, 抛除starts字符 
    ++ pos_beg;
    auto pos_end = std::find(pos_beg, input.end(), ends);
    // 最后一个字符不要，迭代器的索引其实也是包左不包右，左闭右开
    return std::string(pos_beg, pos_end);
}

boost::string_ref between(const boost::string_ref& input, char starts, char ends) {
    auto pos_beg = std::find(input.cbegin(), input.cend(), starts);
    if(pos_beg == input.cend()) {
        return boost::string_ref();
    }

    ++ pos_beg;
    auto pos_end = std::find(pos_beg, input.cend(), ends);
    return boost::string_ref(pos_beg, pos_end - pos_beg);
}

void string_ref_init_examples() {
    // 使用const char*初始化 string_ref
    boost::string_ref r0("^_^");  
    // 使用std::string初始化string_ref
    std::string O_O("O_O");
    boost::string_ref r1 = O_O;
    // 使用std::vector初始化string_ref
    std::vector<char> chars_vec(10, '#');
    boost::string_ref r2(&chars_vec.front(), chars_vec.size());
    
    // 避免编译器未使用警告
    (void) r0;
    (void) r1;
    (void) r2;
}

void string_ref_algorithm_examples() {
    boost::string_ref r("O_O");
    // 查找_符号
    std::find(r.cbegin(), r.cend(), '_');
    // 转换成小写并打印到标准输出
    boost::to_lower_copy(std::ostream_iterator<char>(std::cout), r);
    std::cout << '\n';
    // 打印原字符串
    std::cout << r << '\n';

    // 替换O为^并打印
    boost::replace_all_copy(std::ostream_iterator<char>(std::cout), r, "O", "^");

    std::cout << '\n';

    // 验证boost::lexical_cast可用
    r = "100";
    assert(boost::lexical_cast<int>(r) == 100);
}

int main(int argc, char* argv[]) {
    // 验证const char*可用于构造string_ref
    std::cout << between("Getting expression (between brackets)", '(', ')') << '\n';
    // 验证std::string可用于构造string_ref
    std::string s("(expression)");
    std::cout << between(s, '(', ')') << '\n';

    string_ref_init_examples();
    string_ref_algorithm_examples();
}
