#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <iostream>
#include <string>

// 名称空间简化，重命名
namespace ba = boost::algorithm;

const std::string str = "Hello, hello, dear reader.";

// 擦除字符串中特定字符的例子
void erasing_examples() {
    std::cout << "\n erase all copy   :" << ba::erase_all_copy(str, ",");
    std::cout << "\n erase first copy :" << ba::erase_first_copy(str, ",");
    std::cout << "\n erase last copy  :" << ba::erase_last_copy(str, ",");
    std::cout << "\n ierase all copy  :" << ba::ierase_all_copy(str, "hello");
    std::cout << "\n ierase nth copy  :" << ba::ierase_nth_copy(str, ",", 1);
}

void replacing_examples() {
    std::cout << "\n replace all copy   :" << ba::replace_all_copy(str, ",", "!");
    std::cout << "\n replace first copy :" << ba::replace_first_copy(str, ",", "!");    
    std::cout << "\n replace head copy  :" << ba::replace_head_copy(str, 6, "Whaaaaaaaaaaa!");
}

int main(int argc, char* argv[]) {
    erasing_examples();
    replacing_examples();
}
