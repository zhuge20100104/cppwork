#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <array>

int main() {
    // std::string的操作
    std::string s = "Hello";
    std::reverse(std::begin(s), std::end(s));
    std::cout << s << std::endl;

    // c风格string的操作
    char chs[] = "Hello";
    std::reverse(chs, chs + std::strlen(chs));
    std::cout << chs << std::endl;

    // std::array字符串操作
    std::array<char, 6> strArr{"Hello"};
    std::reverse(begin(strArr), end(strArr));
    std::for_each(std::begin(strArr), std::end(strArr), [](const auto& c){
        std::cout <<c;
    });
    std::cout << std::endl;
}