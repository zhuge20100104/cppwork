#include "chat_message.h"
#include "json_object.h"

#include <boost/asio.hpp>
#include <deque>
#include <iostream>
#include <thread>

#include <cstdlib>

using boost::asio::ip::tcp;

using chat_message_queue = std::deque<chat_message>;

class chat_client {
    public:
        chat_client(boost::asio::io_service& io_service,
                    tcp::resolver::iterator endpoint_iterator
                ): io_service_(io_service), socket_(io_service) {
            do_connect(endpoint_iterator);
        }

        void write(const chat_message& msg) {
            // write是由主线程往子线程写东西
            // 所以需要使用post提交到子线程运行
            // 使得所有io操作都由io_service的子线程掌握
            io_service_.post(
                    [this, msg] () {

                        bool write_in_progress = !write_msgs_.empty();
                        write_msgs_.push_back(msg);
                        if(!write_in_progress) {
                            do_write();
                        }
                    }
                    );
        } 

        
        void close() {
            io_service_.post(
                    [this] () {
                        socket_.close();
                    }
                    );
        }
    private:
      
        void do_connect(tcp::resolver::iterator endpoint_iterator) {
            boost::asio::async_connect(
                        socket_,
                        endpoint_iterator,
                        [this] (boost::system::error_code ec, tcp::resolver::iterator it) {
                            if(!ec) {
                                // 如果连接成功，读取消息头
                                do_read_header();
                            }
                        }
                    );
        }


        void do_read_header() {
            boost::asio::async_read(
                        socket_,
                        boost::asio::buffer(read_msg_.data(), chat_message::header_length),
                        [this] (boost::system::error_code ec, std::size_t length) {
                            if(!ec && read_msg_.decode_header()) {
                                // 如果没有错误，并且Decode_header成功，成功读取到body_length
                                do_read_body();
                            }else {
                                // 读取失败时关闭与服务端的连接，退出事件循环
                                socket_.close();
                            }
                        }
                    );
        }
        
        void toPtree(ptree& tree) {
            std::string buffer(read_msg_.body(), read_msg_.body() + read_msg_.body_length());
            std::stringstream ss(buffer);
            boost::property_tree::read_json(ss, tree);
        } 

        void do_read_body() {
            boost::asio::async_read(
                        socket_,
                        boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
                        [this] (boost::system::error_code ec, std::size_t length) {
                            if(!ec) {
                                // 校验一下消息长度和消息类型，
                                // 证明确实发过来的是RomInformation消息
                                if(read_msg_.type() == MT_ROOM_INFO) {
                                    ptree tree;
                                    toPtree(tree);
                                    std::cout << "client ";
                                    std::cout << tree.get<std::string>("name");
                                    std::cout << " says: ";
                                    std::cout << tree.get<std::string>("information");
                                    std::cout << "\n";
                                    
                                }
                                // 调用do_read_header函数串联起事件链，接着读
                                do_read_header();
                            }else {
                                socket_.close();
                            }
                            
                        }
                    );
        }
        
        // 向服务端真正发送消息的函数
        void do_write() {
            boost::asio::async_write(
                        socket_,
                        boost::asio::buffer(
                            write_msgs_.front().data(),
                            write_msgs_.front().length()
                            ),
                        [this] (boost::system::error_code ec, std::size_t length) {
                            if(!ec) {
                                // 一直写直到写完
                                write_msgs_.pop_front();
                                if(!write_msgs_.empty()) {
                                    do_write();
                                }
                            }else {
                                socket_.close();
                            }
                        }
                    );
        }

        // 注意使用了引用类型,
        // io_service对象的生命周期必须要大于chat_client对象的生命周期
        // 否则会出现引用失效，导致异常
        boost::asio::io_service& io_service_;
        tcp::socket socket_;
        chat_message read_msg_;
        chat_message_queue write_msgs_;
};


int main(int argc, char* argv[]) {
    try {
        if(argc != 3) {
            std::cerr << "Usage: chat_client <host> <port>" << std::endl;
            return 1;
        }

        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        auto endpoint_iterator = resolver.resolve({argv[1], argv[2]});
        chat_client c(io_service, endpoint_iterator);

        std::thread t([&io_service]() {io_service.run(); });
        char line[chat_message::max_body_length + 1];

        // Ctrl + D 正常退出一个应用程序
        while(std::cin.getline(line, chat_message::max_body_length+1)) {
            chat_message msg;
            auto type = 0;

            std::string input(line, line + std::strlen(line));
            std::string output;
            
            if(parseMessage(input, &type, output)) {
                msg.setMessage(type, output.data(), output.size());
                c.write(msg);
            }
        }

        c.close();
        t.join();

    }catch(std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}



