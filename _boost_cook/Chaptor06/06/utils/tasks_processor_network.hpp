#ifndef _CHAPTOR06_06_TASKS_PROCESSOR_NETWORK_HPP_
#define _CHAPTOR06_06_TASKS_PROCESSOR_NETWORK_HPP_
// 给task_processor_timer加上网络处理功能
#include "tasks_processor_timer.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/lexical_cast.hpp>

#include <map>

// 将当前TCP连接的套接字
// 和读取，写入，关闭函数绑定
class tcp_connection_ptr {

    boost::shared_ptr<boost::asio::ip::tcp::socket> socket_;
    public:

        explicit tcp_connection_ptr(boost::shared_ptr<boost::asio::ip::tcp::socket> socket):
            socket_(socket)
         {}

        explicit tcp_connection_ptr(
            boost::asio::io_service& ios,
            const boost::asio::ip::tcp::endpoint& endpoint
        ):
              socket_(boost::make_shared<boost::asio::ip::tcp::socket>(ios))
        {    
                socket_->connect(endpoint);
        }

        template <class Functor>
        void async_write(
            const boost::asio::const_buffers_1& buf, const Functor& f
        ) {
            boost::asio::async_write(*socket_, buf, f);
        }
        
        template <class Functor>
        void async_write(
            const boost::asio::mutable_buffers_1& buf, const Functor& f
        ) {
            boost::asio::async_write(*socket_, buf, f);
        }

        template <class Functor>
        void async_read(
            const boost::asio::mutable_buffers_1& buf, 
            const Functor& f,
            std::size_t at_least_bytes
        ) {
            boost::asio::async_read(
                *socket_, buf, boost::asio::transfer_at_least(at_least_bytes), f
            );
        }

        void shutdown() const {
            socket_->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
            socket_->close();
        }
};

namespace detail {
    // tcp 接收器类，循环接收TCP连接，
    class tcp_listener: public boost::enable_shared_from_this<tcp_listener> {
        using acceptor_t = boost::asio::ip::tcp::acceptor;
        acceptor_t acceptor_;
        boost::asio::io_service& io_service_;

        boost::function<void(tcp_connection_ptr)> func_;

        public:
            template <class Functor> 
            tcp_listener(
                boost::asio::io_service& io_service,
                unsigned short port,
                const Functor& task_unwrapped
            ):
                io_service_(io_service),
                acceptor_(io_service, boost::asio::ip::tcp::endpoint(
                    boost::asio::ip::tcp::v4(), port
                )),
                func_(task_unwrapped)
             {}
            

            void stop() {
                acceptor_.close();
            }

            // 主要用来接收连接，串起接收链
            void push_task() {
                // acceptor 关闭， 不能再接收连接
                if(!acceptor_.is_open()) {
                    return;
                }

                using socket_t = boost::asio::ip::tcp::socket;
                boost::shared_ptr<socket_t> socket = 
                    boost::make_shared<socket_t>(io_service_);

                auto self(shared_from_this());
                tcp_connection_ptr new_connection(socket);
                acceptor_.async_accept(*socket, [self, new_connection](const boost::system::error_code& ec) {
                    self->handle_accept(new_connection, ec);
                }); 

            }
        
        private:
            void handle_accept(
                const tcp_connection_ptr& new_connection,
                const boost::system::error_code& error
            ) {
                // 继续串起接收链，接收下一个新连接
                push_task();
                // 说明async_accept成功
                if(!error) {
                    auto self(shared_from_this());
                    // 连接成功以后，构造一个task_wrapped，执行一下函数
                    make_task_wrapped([self, new_connection](){
                        self->func_(new_connection);
                    })
                    ();
                } else {
                    std::cerr << error << '\n';
                }
            }


    };
}; // namespace detail


namespace tp_network {
    class tasks_processor: public tp_timers::tasks_processor {
        using listeners_map_t = std::map<
            unsigned short, 
            boost::shared_ptr<detail::tcp_listener>
        >;
        listeners_map_t listeners;

        public:
            // 获取全局单例的get方法
            static tasks_processor& get();

            template <class Functor>
            void add_listener(unsigned short port_num, const Functor& f) {
                auto it = listeners.find(port_num);
                // 这个端口在listeners map中已经存在，不需要重复添加
                if(it != listeners.end()) {
                    throw std::logic_error(
                        "Such listener for port '" +
                        boost::lexical_cast<std::string>(port_num) +
                        "' already created"
                    );
                }
                listeners[port_num] = boost::make_shared<detail::tcp_listener>(boost::ref(ios_), port_num, f);
                listeners[port_num]->push_task(); // 开始接收连接，之后一直接收
            }

            void remove_listener(unsigned short port_num) {
                auto it = listeners.find(port_num);
                // 没找着，没法移除
                if(it == listeners.end()) {
                    throw std::logic_error(
                        "No listener for port '" +
                        boost::lexical_cast<std::string>(port_num) +
                        "' created"
                    );
                } 
                (*it).second->stop();
                listeners.erase(it);
            }
            
            tcp_connection_ptr create_connection(const char* addr, unsigned short port_num) {
                return tcp_connection_ptr(ios_, boost::asio::ip::tcp::endpoint(
                    boost::asio::ip::address_v4::from_string(addr),
                    port_num
                ));
            }
    };

    tasks_processor& tasks_processor::get() {
        static tasks_processor proc;
        return proc;
    }
}; // namespace tp_network
#endif