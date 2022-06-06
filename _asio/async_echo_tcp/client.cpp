#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>

#include <string>
#include <iostream>
using namespace boost::asio;

io_service service;

class talk_to_server: public boost::enable_shared_from_this<talk_to_server>, boost::noncopyable {
    talk_to_server(const std::string& message): sock_(service), started_(true), message_(message) {}
    
    void start_(ip::tcp::endpoint ep) {
        auto self(shared_from_this());
        sock_.async_connect(ep, [self](const boost::system::error_code& ec){
                    self->on_connect(ec);
                });
    }

    public:

        using ptr = boost::shared_ptr<talk_to_server>;
        
        static ptr start(ip::tcp::endpoint ep, const std::string& msg ) {
            ptr new_(new talk_to_server(msg));
            new_->start_(ep);
            return new_;
        }

        void stop() {
            if(!started_) return;
            started_ = false;
            sock_.close();
        }

        bool started() { return started_; }
    
    private:

        void on_connect(const boost::system::error_code& ec) {
            if(!ec) {
                do_write(message_+"\n");
            } else {
                stop();
            }
        }
    
        // 开始向服务端写数据
        void do_write(const std::string& msg) {
            if(!started_) {
                return;
            }

            std::copy(msg.begin(), msg.end(), write_buffer_);
            auto self(shared_from_this());
            sock_.async_write_some(buffer(write_buffer_, msg.size()),
                    [self](const boost::system::error_code& ec, std::size_t size) {
                        self->on_write(ec, size);
                    }
                    );
        }

        void on_write(const boost::system::error_code& ec, std::size_t size) {
           do_read(); 
        }

        void do_read() {
            auto self(shared_from_this());
            auto self_read(shared_from_this());

            async_read(sock_, buffer(read_buffer_), 
                        [self](const auto& ec, std::size_t bytes_) {
                            return self->read_complete(ec, bytes_);
                        },
                        [self_read](const auto& ec, std::size_t bytes_) {
                            self_read->on_read(ec, bytes_);
                        }
                    );
        }
        
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

        void on_read(const boost::system::error_code& ec, std::size_t size) {
            if(!ec) {
                // 去掉换行符
                std::string copy(read_buffer_, size-1);
                std::cout << "server echo our message: " << message_
                    << " " << (copy == message_? "OK": "FAIL") << std::endl;
            }
            stop();
        }

        ip::tcp::socket sock_;
        enum {max_msg = 1024};
        char read_buffer_[max_msg];
        char write_buffer_[max_msg];
        bool started_;
        std::string message_;
};

int main(int argc, char* argv[]) {
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8001);
    const char* messages[] = {"John says hi", "so does James", "Lucy just got home", 0};
   
    for(const char** message=messages; *message; ++message) {
        auto client =  talk_to_server::start(ep, *message);
        boost::this_thread::sleep(boost::posix_time::millisec(100));
    }

    service.run();
}
