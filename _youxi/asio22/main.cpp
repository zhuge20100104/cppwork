#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
 
enum {max_length=1024 };

int main(int argc, char* argv[]) {

    try {
        if(argc != 3) {
            std::cout << "Usage: main [host] [port]\n";
            return 1;
        } 

        boost::asio::io_service io_service;
        tcp::socket s(io_service);
        tcp::resolver resolver(io_service);
        // argv[1], argv[2] 这种写法其实是用 初始化列表方式构造一个 query对象
        // resolver.resolve方法是同步的调用方法，非常低效，可能10秒才返回
        // 实际应用中尽量使用异步调用方法
        boost::asio::connect(s, resolver.resolve({argv[1], argv[2]}));
        std::cout << "Enter message:";
        char request[max_length];
        std::cin.getline(request, max_length);
        std::size_t request_len = std::strlen(request);
        boost::asio::write(s, boost::asio::buffer(request, request_len));

        char reply[max_length];
        std::size_t reply_length = boost::asio::read(s, boost::asio::buffer(reply, request_len));
        std::cout << "Reply is:";
        std::cout.write(reply, reply_length);
        std::cout << "\n";
    }catch(std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}


