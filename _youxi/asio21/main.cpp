#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;


class session: public std::enable_shared_from_this<session> {
    public:
        session(tcp::socket socket): socket_(std::move(socket)) {
            // 不要在此处调用start, 因为对象还没有构造完成，不能调用
            // shared_from_this生成智能指针
        }

        void start() {do_read(); }

    private:
        void do_read() {
            auto self(shared_from_this());
               
            socket_.async_read_some(
                    boost::asio::buffer(data, max_length),
                    [this, self] (boost::system::error_code ec, std::size_t length) {
                        if(!ec) {
                            // 实际读取多少字节就写多少字节
                            do_write(length);
                        }
                    }
                    );
        }


        void do_write(std::size_t length) {
            auto self(shared_from_this());

            boost::asio::async_write(socket_, 
                   boost::asio::buffer(data, length),
                   [self, this](boost::system::error_code ec, std::size_t length) {
                    if(!ec) {
                        // 调起回调链
                        do_read();
                    }
                   }
                   );
        }

        tcp::socket socket_;
        enum {max_length=1024 };
        char data[max_length];
}; 


class server {
    public:
        server(boost::asio::io_service& io_service, short port)
            : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)), 
            socket_(io_service){
        } 


        void start() {
            do_accept();
        }

    private:
        void do_accept() {
            acceptor_.async_accept(
                    socket_, 
                    [this](boost::system::error_code error) {
                        if(!error) {
                            auto newSession = std::make_shared<session>(std::move(socket_));
                            newSession->start();
                        }
                        do_accept();
                    }
                    );
        }

        tcp::acceptor acceptor_;
        tcp::socket socket_;
};


int main(int argc, char* argv[]) {
    
    try {

        if(argc != 2) {
            std::cerr << "Usage: async_tcp_echo_server [port] \n";
            return 1;
        }
        boost::asio::io_service io_service;
        server s(io_service, std::atoi(argv[1]));
        s.start();

        io_service.run();

    }catch(std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    } 
    return 0;
}   
