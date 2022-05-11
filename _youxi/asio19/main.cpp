#include <ctime>

#include <iostream>

using std::cout;
using std::endl;

#include <string>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string() {
    using namespace std;
    auto now = time(nullptr);
    return ctime(&now);
}

int main() {
    try {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));   
        // 进入死循环，
        // 接收来自客户端的请求
        cout << "start service" << endl;
        for(;;) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            std::string message = make_daytime_string();
            boost::system::error_code ignored_error;
            // 这里必须要写一个错误码，否则出错时程序会崩溃，抛出异常
            // 服务器程序崩溃是很蛋疼的事情，一般处理掉错误就可以了
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    }catch(std::exception& ex) {
        std::cerr << ex.what() << endl;
    }

    cout << "bye" << endl;

    return 0;
}



