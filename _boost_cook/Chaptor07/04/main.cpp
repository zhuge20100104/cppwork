#include <boost/regex.hpp>

#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << 
        "Available regex syntaxes:\n" <<
        "\t[0] Perl\n" <<
        "\t[1] Perl case insensitive\n" <<
        "\t[2] POSIX extented\n" <<
        "\t[3] POSIX extented case insensitive\n" <<
        "\t[4] POSIX basic\n" <<
        "\t[5] POSIX basic case insensitive\n" <<
        "Choose regex syntax: ";
    
    boost::regex::flag_type flag;
    // 让用户选择正则表达式语法
    switch(std::cin.get()) {
        case '0':
            flag = boost::regex::perl;
            break;
        case '1':
            flag = boost::regex::perl | boost::regex::icase;
            break;
        case '2':
            flag = boost::regex::extended;
            break;
        case '3':
            flag = boost::regex::extended | boost::regex::icase;
            break;
        case '4':
            flag = boost::regex::basic;
            break;
        case '5':
            flag = boost::regex::basic | boost::regex::icase;
            break;
        default:
            std::cerr << "Incorrect number of regex syntax, Exiting...\n";
            return -1;
    }

    // 不让regex构造函数抛异常
    // 关于C++的两个不成文规定了解下，构造函数有异常需要抛出异常，千万不要在析构函数抛出异常
    // 所以构造函数是可以抛出异常的
    // 这里不让构造函数 抛出异常的原因是，在while循环中，一次构造失败不影响下一次输入正确的表达式
    // 可以使用错误码检测的机制来阻止异常发生，而不是简单的抛出异常，停止程序
    // 或者抛出异常，捕获异常
    // 因为根据异常来判断程序是否执行成功不可取，这种代码不具有可测性，不到不得已不要为之
    // 面试中写出根据异常判断程序是否成功，估计就要等通知了
    flag |= boost::regex::no_except;
    // 清空std::cin
    std::cin.ignore();
    std::cin.clear();

    std::string regex, str;

    do {
        std::cout << "Input regex: ";
        if(!std::getline(std::cin, regex) || regex.empty()) {
            return 0;
        }
        // 如果不设置 不抛出异常，构造函数可能会抛出异常
        const boost::regex e(regex, flag);
        if(e.status()) {
            std::cerr << "Incorrect regex pattern!\n";
            continue;
        }

        std::cout << "String to match: ";
        while(std::getline(std::cin, str) && !str.empty()) {
            bool matched = boost::regex_match(str, e);
            std::cout << (matched ? "MATCH\n": "DOES NOT MATCH\n");
            std::cout << "String to match: ";
        }

        std::cout << '\n';
        // 清空std::cin
        std::cin.ignore();
        std::cin.clear();
    } while(1);
}