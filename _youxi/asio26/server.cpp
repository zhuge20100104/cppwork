#include "chat_message.h"
#include "json_object.h"

#include <boost/asio.hpp>

#include <deque>
#include <iostream>
#include <memory>
#include <set>
#include <list>
#include <utility>

#include <cassert>
#include <cstdlib>

using boost::asio::ip::tcp;

using chat_message_queue = std::deque<chat_message>;

class chat_session;
using chat_session_ptr = std::shared_ptr<chat_session>;

// 聊天室类的声明
class chat_room {
    public:
        void join(chat_session_ptr);
        void leave(chat_session_ptr);
        void deliver(const chat_message&);
    private:
        std::set<chat_session_ptr> participants_;
        enum { max_recent_msgs = 100 };
        chat_message_queue recent_msgs_;
};

class chat_session: public std::enable_shared_from_this<chat_session> {
    public:
        chat_session(tcp::socket socket, chat_room& room): socket_(std::move(socket)), room_(room) {}

        void start() {
            room_.join(shared_from_this());
            // 启动服务时开始读取消息头
            do_read_header();
        }

        void deliver(const chat_message& msg) {
            bool write_in_progress = !write_msgs_.empty();
            write_msgs_.push_back(msg);            

            // 为了保护do_write线程里面的deque，避免两个线程同时写
            if(!write_in_progress) {
                do_write();
            }
        }
    private:
        // 读取消息头
        void do_read_header() {
            auto self(shared_from_this());

            boost::asio::async_read(
                        socket_,
                        boost::asio::buffer(read_msg_.data(), chat_message::header_length),
                        [this, self] (boost::system::error_code ec, std::size_t length) {
                            // 头部解析成功，获取到body_length
                            if(!ec && read_msg_.decode_header()) {
                                do_read_body();
                            } else {
                                room_.leave(shared_from_this());
                            }
                        }
                    );
        }


        void do_read_body() {
            auto self(shared_from_this());

            boost::asio::async_read(
                    socket_,
                    boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
                    [this, self] (boost::system::error_code ec, std::size_t length) {
                        // 如果读取消息成功，没有error
                        if(!ec) {
                            // room_的deliver msg，会先更新recent_message queue,
                            // 然后调用各;个Session的Deliver message
                            // 将消息发给对应的client 
                            // room_.deliver(read_msg_);
                            handleMessage();
                            
                            // 接着读头，形成事件循环
                            do_read_header();
                        }else {
                            room_.leave(shared_from_this());
                        }
                    }
                );
        }
        

        
        ptree toPtree() {
            std::string buffer(read_msg_.body(), read_msg_.body() + read_msg_.body_length());
            std::cout << "raw message server: " << buffer << std::endl; 
            std::stringstream ss(buffer);
            ptree tree;
            try {
                boost::property_tree::read_json(ss, tree);
            }catch(std::exception& ex) {
                std::cerr << "解析 property_tree 失败!!" << std::endl;
                std::cerr << ex.what() << std::endl;
            }
            return tree;
        }
    
        // 处理接收到的客户端的消息的函数
        void handleMessage() {
            if(read_msg_.type() == MT_BIND_NAME) {
                ptree tree = toPtree();
                m_name = tree.get<std::string>("name");
            } else if(read_msg_.type() == MT_CHAT_INFO) {
                ptree tree = toPtree();
                m_chatInformation = tree.get<std::string>("information");
                auto rinfo = buildRoomInfo();
                chat_message msg;
                msg.setMessage(MT_ROOM_INFO, rinfo);
                room_.deliver(msg);
            } else {
                //不可用消息，啥也不做
            }
        }
        
        // 构建一个RoomInformation信息
        std::string buildRoomInfo() const {
            ptree tree;
            tree.put("name", m_name);
            tree.put("information", m_chatInformation);
            return ptreeToJsonString(tree);
        }

        void do_write() {
            auto self(shared_from_this());
            boost::asio::async_write(
                        socket_,
                        boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()),
                        [this, self] (boost::system::error_code ec, std::size_t length) {
                            // 如果写队头信息成功，没有错误    
                            if(!ec) {

                                write_msgs_.pop_front();
                                // 如果还有得写，就接着写
                                if(!write_msgs_.empty()) {
                                    do_write();
                                }
                            }else {
                                room_.leave(shared_from_this());
                            }
                        }
                    );
        }

        tcp::socket socket_;
        // room的生命周期必须长于session的生命周期，
        // 否则会因为持有无效的引用而翻车
        chat_room& room_;
        chat_message read_msg_;
        chat_message_queue write_msgs_;
        std::string m_name; // 客户端姓名
        std::string m_chatInformation; // 客户端当前的消息
};


void chat_room::join(chat_session_ptr participant) {
    participants_.insert(participant);
    
    // 给新加入者广播一遍历史消息
    for(const auto& msg: recent_msgs_) {
        participant->deliver(msg);
    }
}

void chat_room::leave(chat_session_ptr participant) {
    participants_.erase(participant);
}

// 消息分发函数
void chat_room::deliver(const chat_message& msg) {
    recent_msgs_.push_back(msg);
    // recent_msgs_调整到最大值
    while(recent_msgs_.size() > max_recent_msgs) {
        recent_msgs_.pop_front();
    }

    // 给每个群聊参与者群发消息
    for(auto & participant: participants_) {
        participant->deliver(msg);
    }
}


class chat_server {
    public:
        chat_server(boost::asio::io_service& io_service, 
                    const tcp::endpoint& endpoint): acceptor_(io_service, endpoint), 
                                                    socket_(io_service){
                                                        do_accept();
                                                    }
        
        // 接收来自客户端的连接的函数
        void do_accept() {
            acceptor_.async_accept(
                        socket_, 
                        [this] (boost::system::error_code ec) {
                            // 如果接收连接成功，没有错误
                            if(!ec) {
                                auto session = std::make_shared<chat_session>(std::move(socket_),
                                        room_
                                    );

                                session->start();
                            } 

                            // 无论成功或失败，都继续接收连接
                            do_accept();
                        }
                    );
        }
    private:
        tcp::acceptor acceptor_;
        tcp::socket socket_;
        chat_room room_;
};


int main(int argc, char* argv[]) {

    try {
        if(argc < 2) {
            std::cerr << "Usage: chat_server <port> [<port> ...]" << std::endl;
            return 1;
        }
        
        boost::asio::io_service io_service;

        std::list<chat_server> servers;
        
        for(int i=1; i<argc; ++i) {
            tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
            servers.emplace_back(io_service, endpoint);
        }
        io_service.run();

    }catch(std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl; 
    }

    return 0;
}

