#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <iostream>

// 停止解析的标记
bool stop_parsing = true;
// 未完成解析标记
bool not_end_of_parsing = true;

// do_parse线程函数声明
void do_parse();

int main(int argc, char* argv[]) {
    boost::thread parse_thread(&do_parse);

    // sleep 200微秒，等待子线程解析过程运行
    // 否则看不出中断的效果
    boost::this_thread::sleep(boost::posix_time::microseconds(200));

    if(stop_parsing) {
        // 不需要继续解析了,中断子线程并退出
        parse_thread.interrupt();
    }

    parse_thread.join();
    std::cout << "After interuptted ..." << std::endl;
}

// 解析方法实现
void do_parse() {
    // 未结束解析
    while(not_end_of_parsing) {
        std::cout << "Before interuptted ..." << std::endl;
        // 中断点，中断时的退出位置
        boost::this_thread::interruption_point();

        std::cout << "I'm parsing ... " << std::endl;
    }
}
