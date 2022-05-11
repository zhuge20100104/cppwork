#include <boost/regex.hpp>

#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Availables regex syntaxes: \n" <<
        "\t[0] Perl\n" <<
        "\t[1] Perl case insensitive\n" <<
        "\t[2] Posix extended\n" <<
        "\t[3] Posix extended case insensitive\n" <<
        "\t[4] Posix basic\n" <<
        "\t[5] Posix basic case insensitive\n" <<
        "Choose regex syntax: ";
    
    boost::regex::flag_type flag;

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
            std::cout << "Incorrect number of regex syntax. Exiting...\n";
            return -1;
    }

    // 禁止抛出异常，原因和上节一样
    flag |= boost::regex::no_except;
   
    // 清空std::cin
    std::cin.ignore();
    std::cin.clear();

    std::string regex, str, replace_string;

    do {
        std::cout << "\nInput regex: ";
        // 未获取到正则表达式，返回
        if(!std::getline(std::cin, regex) || regex.empty()) {
            return 0;
        }
        // 若flag标志位中不设置禁止异常，构造函数可能抛出异常，
        // 不方便测试和维护
        const boost::regex e(regex, flag);
        if(e.status()) {
            std::cout << "Incorrect regex pattern!\n";
            continue;
        }

        std::cout << "String to match: ";
        while(std::getline(std::cin, str) && !str.empty()) {
            // 这个返回值值得详细讲解下，直接看源码
            // 这是smatch的定义，smatch被定义为match_results
            // typedef match_results<std::string::const_iterator> smatch;
            //
            // match_results中有这样一个结构来保存结果,这里的BidiIterator可以理解为std::string::const_iterator
            // 更简单一点的理解是 iterator<const char*>
            // 所以说如下定义可以替换为 std::vector<sub_match<iterator<const char*> > >
            // typedef std::vector<sub_match<BidiIterator>, Allocator> vector_type;
            // 
            // 再往下看sub_match的定义
            // struct sub_match : public std::pair<BidiIterator, BidiIterator>
            // 这就很简单了，
            // 整体的结构就是 std::vector<std::pair<iterator<const char*>, iterator<const char*> > >
            // 其中第一层迭代器代表 若干个字符串， 例如 regex是 he(.*)ow(.*)ld，待匹配串是helloworld，
            // 那么第一层迭代器指向{"ll", "or"} 这个数组中的元素
            // 第二层迭代器是一个pair，pair的first是数组每个元素的 起始字母，pair的second是数组每个元素的结束字母
            // 例如，对于 ll来说，first指向第一个l, second指向第二个l之后
            // 
            // 有一个特例，boost C++和java一样，第一个返回的第一个匹配串是原串，例如上例的第一个匹配串是 helloworld
            boost::smatch results;
            bool matched = regex_search(str, results, e);
            if(matched) {
                std::cout << "MATCH: ";
                // 匹配成功之后打印出所有匹配串，以，分割
                std::copy(
                        results.begin() + 1,
                        results.end(),
                        std::ostream_iterator<std::string>(std::cout, ", ")
                );

                // 请输入替换字符
                std::cout << "\nReplace pattern: ";
                if(std::getline(std::cin, replace_string) && !replace_string.empty()) {
                    // 开始做替换
                    std::string res = "";
                    for(auto it = results.begin() + 1, it_end = results.end(); it != it_end; ++it) {
                        res = str.replace(it->begin(), it->end(), replace_string);
                    }
                    std::cout << "RESULT: " << str << std::endl;
                }else {
                    std::cin.ignore();
                    std::cin.clear();
                }
            }else {
                std::cout << "DOES NOT MATCH";
            }

            std::cout << "\n String to match: ";
        }
    } while(1);

    return 0;
}