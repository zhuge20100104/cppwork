#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <iostream>
#include <string>

using namespace boost::asio;
using namespace boost::posix_time;
using boost::system::error_code;

io_service service;

std::size_t read_complete(char* buf, const boost::system::error_code& ec, std::size_t bytes_) {
    if(ec && ec != boost::asio::error::eof) {
        std::cerr << "An error occurred, error info: " << ec.message() << std::endl;
        return 0;
    } else if(ec) {
        // EOF, 直接退出，return 0
        return 0;
    }

    // 读到出现换行符为止
    bool find = std::find(buf, buf+bytes_, '\n') < buf + bytes_;
    return find ? 0: 1;
}


// 接收客户端连接并处理的函数
void handle_connections() {
    ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8001));
    char buff[1024];
    char* buf = buff;

    // 一直阻塞等待，只要有连接进来就连接
    while(true) {
        // 准备一个与客户端的连接
        ip::tcp::socket sock(service);
        acceptor.accept(sock);
        int bytes = read(sock, buffer(buff), 
                [buf](const auto& ec, std::size_t size_){
                    return read_complete(buf, ec, size_);
                });

        std::string msg(buff, buff+bytes);
        sock.write_some(buffer(msg));
        sock.close();
    }
}

int main(int argc, char* argv[]) {
    handle_connections();
    return 0;
}
