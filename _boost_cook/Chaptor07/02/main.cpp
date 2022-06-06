#include <boost/format.hpp>
// 注意转义字符 %% 表示 一个 %的用法

#include <iostream>

class i_hold_some_internals {
    int i;
    std::string s;
    char c;

    public:
        i_hold_some_internals():
            i(100),
            s("Reader"),
            c('!')
         {}

        // 格式化参数必须包含下面的字符
        // %1% i
        // %2% s
        // %3% c
        std::string to_string(const std::string& format_specifier) const {
            boost::format f(format_specifier);
            // 去掉too_many_args_bit位，保留其他位
            unsigned char flags = boost::io::all_error_bits;
            flags ^= boost::io::too_many_args_bit;
            f.exceptions(flags);
            return (f % i % s % c).str();
        }
};

int main(int argc, char* argv[]) {
    i_hold_some_internals class_instance;
    std::cout << class_instance.to_string(
        "Hello, dear %2%! "
        "Did you read the book for %1% %% %3%\n");
    
    std::cout << class_instance.to_string(
        "%1% == %1% && %1% %% != %1%\n\n"
    );

    // 输出 "Reader"
    std::cout << class_instance.to_string("%2%\n\n");

    try {
        class_instance.to_string("%1% %2% %3% %4% %5%\n");
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}
 