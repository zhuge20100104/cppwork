#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <chrono>
#include <ctime>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <sstream>

namespace _time {
    // 日期时间格式化的常量字符串
    static const std::string TIME_FORMAT = "%Y-%m-%d %H:%M:%S";
    // 重命名system_clock名称空间
    using system_clk = std::chrono::system_clock;
    // 重命名time_point类型
    using _time_point = std::chrono::time_point<system_clk>;

    class Timer {
        public: 
            Timer(): m_begin(system_clk::now()) {}
            
            void reset() {
                m_begin = system_clk::now();
            }

            // 将时间点信息转换为字符串的函数
            bool to_string(const _time_point& t, const std::string& date_fmt, std::string& result) {
                std::time_t c_time_t = system_clk::to_time_t(t);
                char mbstr[100];
                size_t size = std::strftime(mbstr, sizeof(mbstr), date_fmt.c_str(), std::localtime(&c_time_t));
                if(size) {
                    result = mbstr;
                    return true;
                }
                return false;
            } 

            // 将字符串转换为time_point的函数
            void from_string(const std::string &src_str, const std::string& date_fmt, _time_point& out_t) {
                std::stringstream ss{src_str};
                std::tm dt;
                ss >> std::get_time(&dt, date_fmt.c_str());
                time_t c_time_t = std::mktime(&dt);
                out_t = system_clk::from_time_t(c_time_t);
            }

            // 默认输出毫秒
            int64_t elapsed() const {
                return std::chrono::duration_cast<std::chrono::milliseconds>(system_clk::now() - m_begin).count();
            }

            // 微秒
            int64_t elapsed_micro() const {
                return std::chrono::duration_cast<std::chrono::microseconds>(system_clk::now() - m_begin).count();
            }

            // 纳秒
            int64_t elapsed_nano() const {
                return std::chrono::duration_cast<std::chrono::nanoseconds>(system_clk::now() - m_begin).count();
            }

            // 秒
            int64_t elapsed_sec() const {
                return std::chrono::duration_cast<std::chrono::seconds>(system_clk::now() - m_begin).count();
            }

            // 分
            int64_t elapsed_min() const {
                return std::chrono::duration_cast<std::chrono::minutes>(system_clk::now() - m_begin).count();
            }

            // 时
            int64_t elapsed_hour() const {
                return std::chrono::duration_cast<std::chrono::hours>(system_clk::now() - m_begin).count();
            }

        private:
            _time_point m_begin;
    };
};
#endif