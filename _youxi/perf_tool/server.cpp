#include "utils/chat_message.h"
#include "utils/cfg_reader.h"

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <cassert>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>


using boost::asio::ip::tcp;

using chat_message_queue = std::deque<chat_message>;

class chat_session;
using chat_session_ptr = std::shared_ptr<chat_session>;

std::string master_name = "";

std::map<std::string, std::string> server_cfg {};

// 聊天室类的声明
class chat_room {
   public:
    chat_room(boost::asio::io_service& io_service_): m_strand(io_service_)  {}
    void join(chat_session_ptr);
    void leave(chat_session_ptr);
    void deliver(const chat_message&);
    void deliver_to(const chat_message&, const std::string& paticipant_name);

   private:
    boost::asio::io_service::strand m_strand;
    std::set<chat_session_ptr> participants_;
};

class chat_session : public std::enable_shared_from_this<chat_session> {
   public:
    chat_session(tcp::socket socket, chat_room& room)
        : socket_(std::move(socket)), room_(room){
            
        }

    void start() {
        room_.join(shared_from_this());

        // 使用协程 同时读取头和body
        read_header_and_body();
    }

    void deliver(const chat_message& msg) {
        bool write_in_progress = !write_msgs_.empty();
        write_msgs_.push_back(msg);

        // 为了保护do_write线程里面的deque，避免两个线程同时写
        if (!write_in_progress) {
            do_write();
        }
    }

    std::string& get_client_name() { return m_name; }

   private:
    void read_header_and_body() {
        auto self(shared_from_this());
        boost::asio::spawn(
            socket_.get_executor(),
            [this, self](boost::asio::yield_context yield) {
                while (true) {
                    boost::system::error_code ec_header;
                    boost::asio::async_read(
                        socket_,
                        boost::asio::buffer(read_msg_.data(),
                                            chat_message::header_length),
                        yield[ec_header]);
                    if (!ec_header & read_msg_.decode_header()) {
                        boost::system::error_code ec_body;
                        // 在这里read body
                        boost::asio::async_read(
                            socket_,
                            boost::asio::buffer(read_msg_.body(),
                                                read_msg_.body_length()),
                            yield[ec_body]);

                        // 如果读取消息成功，没有error
                        if (!ec_body) {
                            // 调用各个Session的Deliver message
                            // 将消息发给对应的client
                            // room_.deliver(read_msg_);
                            handleMessage();
                        } else {
                            room_.leave(shared_from_this());
                        }

                    } else {
                        room_.leave(shared_from_this());
                    }
                }
            });
    }

    json to_json() {
        std::string buffer(read_msg_.body(),
                           read_msg_.body() + read_msg_.body_length());
        std::cout << "raw message server: " << buffer << std::endl;
        std::stringstream ss(buffer);
        json json_obj;
        try {
            json_obj = json::parse(ss.str());
        } catch (std::exception& ex) {
            std::cerr << "解析 json对象 失败!!" << std::endl;
            std::cerr << ex.what() << std::endl;
        }
        return json_obj;
    }

    // 处理接收到的客户端的消息的函数
    void handleMessage() {
        // master 和 slave都会发这个，注册自己的名字
        if (read_msg_.type() == MT_BIND_NAME) {
            auto json_obj = to_json();
            m_name = json_obj["name"].get<std::string>();
            std::cerr << "Bind Name: " << m_name << std::endl;
            // 只有master会发launch task message
        } else if (read_msg_.type() == MT_LAUNCH_TASK_MSG) {
            master_name = m_name;
            std::cerr << "MT_LAUNCH_TASK_MSG: " << std::endl;

            std::cerr << "Master name: " << master_name << std::endl;
            auto json_obj = to_json();
            m_chatInformation = json_obj["information"].get<std::string>();
            auto rinfo = buildRoomInfo();
            chat_message msg;
            msg.setMessage(MT_LAUNCH_TASK_MSG, rinfo);
            room_.deliver(msg);
            // 所有slave执行完性能测试之后，都会发这个消息
        } else if (read_msg_.type() == MT_SEND_TASK_INFO_MSG) {
            std::cerr << "send task info" << std::endl;
            std::cerr << "Master name in task info: " << master_name
                      << std::endl;
            auto json_obj = to_json();
            m_chatInformation = json_obj["information"].get<std::string>();
            auto rinfo = buildRoomInfo();
            chat_message msg;
            msg.setMessage(MT_SEND_TASK_INFO_MSG, rinfo);
            room_.deliver_to(msg, master_name);
        } else {
            // 不可用消息，啥也不做
        }
    }

    // 构建一个RoomInformation信息
    std::string buildRoomInfo() const {
        json msg_body;
        msg_body["name"] = m_name;
        msg_body["information"] = m_chatInformation;
        std::string msg_body_str = msg_body.dump();
        std::cout << "Room info: " << msg_body_str << std::endl;
        return std::move(msg_body_str);
    }

    void do_write() {
        auto self(shared_from_this());
        boost::asio::spawn(
            socket_.get_executor(),
            [this, self](boost::asio::yield_context yield) {
                boost::system::error_code ec;
                boost::asio::async_write(
                    socket_,
                    boost::asio::buffer(write_msgs_.front().data(),
                                        write_msgs_.front().length()),
                    yield[ec]);
                if (!ec) {
                    write_msgs_.pop_front();
                    // 如果还有得写，就接着写
                    if (!write_msgs_.empty()) {
                        do_write();
                    }
                } else {
                    room_.leave(shared_from_this());
                }
            });
    }

    tcp::socket socket_;
    // room的生命周期必须长于session的生命周期，
    // 否则会因为持有无效的引用而翻车
    chat_room& room_;
    chat_message read_msg_;
    chat_message_queue write_msgs_;
    std::string m_name;             // 客户端姓名
    std::string m_chatInformation;  // 客户端当前的消息
};

void chat_room::join(chat_session_ptr participant) {
    m_strand.post([this, participant] {
        // 不需要广播历史消息这里
        participants_.insert(participant);
    });
}

void chat_room::leave(chat_session_ptr participant) {
    m_strand.post([this, participant]{
        participants_.erase(participant);
    });
}

// 消息分发函数
void chat_room::deliver(const chat_message& msg) {
    m_strand.post([this, msg] {
        // 给每个群聊参与者群发消息
        for (auto& participant : participants_) {
            participant->deliver(msg);
        }
    });
   
}

void chat_room::deliver_to(const chat_message& msg,
                           const std::string& paticipant_name) {

    m_strand.post([this, msg, paticipant_name] {
        // 给每个群聊参与者群发消息
        for (auto& participant : participants_) {
            if (participant->get_client_name() == paticipant_name) {
                participant->deliver(msg);
            }
        }
    });
}

class chat_server {
   public:
    chat_server(boost::asio::io_service& io_service,
                const tcp::endpoint& endpoint)
        : acceptor_(io_service, endpoint), socket_(boost::asio::make_strand(io_service)), room_(io_service) {
        do_accept();
    }

    // 接收来自客户端的连接的函数
    void do_accept() {
        boost::asio::spawn(
            socket_.get_executor(), [this](boost::asio::yield_context yield) {
                while (true) {
                    boost::system::error_code ec;
                    acceptor_.async_accept(socket_, yield[ec]);
                    if (!ec) {
                        auto session = std::make_shared<chat_session>(
                            std::move(socket_), room_);

                        session->start();
                    }
                }
            });
    }

   private:
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    chat_room room_;
};

int main(int argc, char* argv[]) {
    try {
        bool read_res = cfg_reader::read_file(server_cfg_file_path, server_cfg);
        if(!read_res) {
            std::cerr << "Read server config file failed! " << std::endl;
            return 1;
        }

        boost::asio::io_service io_service;
        tcp::endpoint endpoint(tcp::v4(), std::atoi(server_cfg["port"].c_str()));
        chat_server server{io_service, endpoint};

        io_service.run();

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
