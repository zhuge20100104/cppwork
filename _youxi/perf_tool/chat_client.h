#ifndef _FREDRIC_CHAT_CLIENT_H_
#define _FREDRIC_CHAT_CLIENT_H_

#include "chat_message.h"

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>


using boost::asio::ip::tcp;

using chat_message_queue = std::deque<chat_message>;

class chat_client {
   public:
    chat_client(boost::asio::io_service& io_service,
                tcp::resolver::iterator endpoint_iterator)
        : io_service_(io_service), socket_(io_service), work_(io_service) {
        do_connect(endpoint_iterator);
    }

    void write(const chat_message& msg) {
        // write是由主线程往子线程写东西
        // 所以需要使用post提交到子线程运行
        // 使得所有io操作都由io_service的子线程掌握
        io_service_.post([this, msg]() {
            bool write_in_progress = !write_msgs_.empty();
            write_msgs_.push_back(msg);
            if (!write_in_progress) {
                do_write();
            }
        });
    }

    void close() {
        io_service_.post([this]() { socket_.close(); work_.get_io_context().stop(); });
    }

   protected:
    void do_connect(tcp::resolver::iterator endpoint_iterator) {
        boost::asio::spawn(
            socket_.get_executor(),
            [this, endpoint_iterator](boost::asio::yield_context yield) {
                boost::system::error_code conn_ec;
                boost::asio::async_connect(socket_, endpoint_iterator,
                                           yield[conn_ec]);
                if (!conn_ec) {
                    do_read_header_and_body();
                }
            });
    }

    void do_read_header_and_body() {
        boost::asio::spawn(
            socket_.get_executor(), [this](boost::asio::yield_context yield) {
                while (true) {
                    boost::system::error_code header_ec;
                    boost::asio::async_read(
                        socket_,
                        boost::asio::buffer(read_msg_.data(),
                                            chat_message::header_length),
                        yield[header_ec]);

                    if (!header_ec && read_msg_.decode_header()) {
                        boost::system::error_code body_ec;
                        // 如果没有错误，并且Decode_header成功，成功读取到body_length
                        boost::asio::async_read(
                            socket_,
                            boost::asio::buffer(read_msg_.body(),
                                                read_msg_.body_length()),
                            yield[body_ec]);
                        bool stop = receive_msg(body_ec);
                        if(stop) {
                            close();
                            break;
                        }
                    } else {
                        // 读取失败时关闭与服务端的连接，退出事件循环
                        socket_.close();
                    }
                }
            });
    }

    json to_json() {
        std::string buffer(read_msg_.body(),
                           read_msg_.body() + read_msg_.body_length());
        std::stringstream ss(buffer);
        auto json_obj = json::parse(ss.str());
        return json_obj;
    }

    virtual bool receive_msg(const boost::system::error_code& ec) = 0;

    // 向服务端真正发送消息的函数
    void do_write() {
        boost::asio::spawn(
            socket_.get_executor(), [this](boost::asio::yield_context yield) {
                boost::system::error_code ec;

                boost::asio::async_write(
                    socket_,
                    boost::asio::buffer(write_msgs_.front().data(),
                                        write_msgs_.front().length()),
                    yield[ec]);

                if (!ec) {
                    // 一直写直到写完
                    write_msgs_.pop_front();
                    if (!write_msgs_.empty()) {
                        do_write();
                    }
                } else {
                    socket_.close();
                }
            });
    }

    // 注意使用了引用类型,
    // io_service对象的生命周期必须要大于chat_client对象的生命周期
    // 否则会出现引用失效，导致异常
    boost::asio::io_service& io_service_;
    tcp::socket socket_;
    chat_message read_msg_;
    boost::asio::io_service::work work_;
    chat_message_queue write_msgs_;
};

bool parse_and_send_a_message(chat_client& c,
                              const std::string& input_msg_str) {
    chat_message msg;
    auto type = 0;

    std::string output;
    if (parseMessage(input_msg_str, &type, output)) {
        msg.setMessage(type, output.data(), output.size());
        c.write(msg);
        return true;
    } else {
        std::cerr << "Parse message error!" << std::endl;
        return false;
    }
}

#endif