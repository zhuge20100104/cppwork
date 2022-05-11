#ifndef _SCOUT_HPP_
#define _SCOUT_HPP_
#include <mutex>
#include <iostream>
#include <sstream>

class Scout {
    std::ostringstream st;
    // Endl结束符的形式
    using endlFunc = std::ostream& (*)(std::ostream&);

    public:
        // 处理普通模板类输出
        template <typename T>
        Scout& operator<<(const T& t) {
            st << t;
            return *this;
        }

        // 处理换行符
        Scout& operator<<(endlFunc endlF) {
            st << endlF;
            return *this;
        }

        ~Scout() {
            std::string s = st.str();
            // std::cerr不存buffer 直接输出
            std::cerr << s;
        }
};

// 定义一个宏，方便输出
#define scout Scout()

#endif