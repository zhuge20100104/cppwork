#include <boost/noncopyable.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <iostream>

using namespace boost::asio;
using namespace boost::posix_time;

io_service service;

class talk_to_client: public boost::enable_shared_from_this<talk_to_client>, boost::noncopyable {
    public:
        talk_to_client(): sock_(service), started_(false){}
        
        using error_code = boost::system::error_code;
        using ptr = boost::shared_ptr<talk_to_client>;

        static ptr new_() {
            // 改写成C++11 语法形式
            auto client = boost::make_shared<talk_to_client>();
            return client;
        }
        
        void start() {
            started_ = true;
            do_read();
        }

        void stop() {
            if(!started_) {
                return;
            }
            started_ = false;
            sock_.close();
        }

        ip::tcp::socket& sock() {
            return sock_;
        }


    private:
        
        // 读取函数
        void do_read() {
            // 使引用计数连加2次，避免在回调函数中指针失效被释放
            auto self(shared_from_this());
            auto self_read = self;

            async_read(sock_, buffer(read_buffer_),
                    [self] (const boost::system::error_code& ec, std::size_t bytes_) {
                        return self->read_complete(ec, bytes_);
                    },
                    [self_read] (const boost::system::error_code& ec, std::size_t bytes_) {
                        self_read->on_read(ec, bytes_);
                    } 
                    );
        }
        
        // 判断本次读取是否完成的函数，通过换行符判断是否完成
        std::size_t read_complete(const boost::system::error_code& ec, std::size_t bytes_) {
            if(ec && ec != boost::asio::error::eof) {
                std::cerr << "An error occurred, error info: " << ec.message() << std::endl;
                return 0;
            } else if(ec) {
                // EOF, 直接退出，return 0
                return 0;
            }

            // 读到出现换行符为止
            bool find = std::find(read_buffer_, read_buffer_+bytes_, '\n') < read_buffer_ + bytes_;
            return find ? 0: 1;
        }

        // 读取完成之后的回调函数
        void on_read(const boost::system::error_code& ec, std::size_t bytes_) {
            if(!ec) {
                // 回显消息加换行符之后 stop
                std::string msg(read_buffer_, bytes_);
                do_write(msg + "\n");
            }
            stop();
        }

        // 会写消息的函数
        void do_write(const std::string& msg) {
            std::copy(msg.begin(), msg.end(), write_buffer_);
            auto self(shared_from_this());
            sock_.async_write_some(buffer(write_buffer_, msg.size()), 
                        [self](const boost::system::error_code& ec, std::size_t size) {
                            self->on_write(ec, size);
                        }
                    );
        }

        void on_write(const boost::system::error_code& ec, std::size_t bytes_) {
            // on_write 调用do_read构成调用链
            do_read();
        }

        ip::tcp::socket sock_;
        enum {max_msg = 1024};
        char read_buffer_[max_msg];
        char write_buffer_[max_msg];
        bool started_;
};


ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8001));

void handle_accept(talk_to_client::ptr client, const boost::system::error_code& ec) {
    client->start();
    auto new_client = talk_to_client::new_();
    // 引用计数加1，避免提早释放
    talk_to_client::ptr ptr_new = new_client;
    acceptor.async_accept(new_client->sock(), [ptr_new] (const boost::system::error_code& ec) {
                handle_accept(ptr_new, ec);
            });
}

int main(int argc, char* argv[]) {
    auto new_client = talk_to_client::new_();
    // 引用计数加1，避免提早释放
    talk_to_client::ptr ptr_new = new_client;
    acceptor.async_accept(new_client->sock(), [ptr_new] (const boost::system::error_code& ec) {
                handle_accept(ptr_new, ec);
            });

    service.run();
}


