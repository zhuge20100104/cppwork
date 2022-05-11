#include "utils/tasks_processor_network.hpp"

#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>

using namespace tp_network;
// 前向声明
class authorizer;
// 全局的authorizer_ptr声明
using authorizer_ptr = boost::shared_ptr<authorizer>;

class authorizer: public boost::enable_shared_from_this<authorizer> {
    tcp_connection_ptr connection_;
    boost::array<char, 512> message_;

    explicit authorizer(const tcp_connection_ptr& connection):
        connection_(connection) {

    }

    public:
        // 至少读一个字节
        static void on_connection_accept(const tcp_connection_ptr& connection) {
            authorizer_ptr auth(new authorizer(connection));
            auth->connection_.async_read(
                boost::asio::buffer(auth->message_),
                [auth](const boost::system::error_code& ec, std::size_t bytes_transferred) {
                    auth->on_data_received(ec, bytes_transferred);
                },
                1
            );
        }

        void on_data_received(const boost::system::error_code& ec, std::size_t bytes_transferred) {
            if(ec) {
                std::cerr << "authorizer.on_data_received: error during receiving response: " << ec << '\n';
                assert(false);
            }

            if(bytes_transferred == 0) {
                std::cerr << "authorizer.on_data_received: zero bytes received\n";
                assert(false);
            }

            // 现在我们在 message_中读到了数据，我们可以做一些验证登陆的工作
            // ...

            // 往客户端回写消息 ”OK“
            message_[0] = 'O';
            message_[1] = 'K';

            std::size_t bytes_to_send = 2;

            auto self(shared_from_this());
            // 现在把"OK"写回去
            connection_.async_write(
                boost::asio::buffer(message_, bytes_to_send),
                [self](const boost::system::error_code& ec, std::size_t bytes_transferred) {
                    self->on_data_send(ec);
                }
            );
        }

        // 发回客户端数据后的回调函数
        void on_data_send(const boost::system::error_code& ec) {
            if(ec) {
                std::cerr << "authorizer.on_data_send: error during send response: " << ec << '\n';
                assert(false);
            }

            connection_.shutdown();
        }
};

// 全局的是否auth成功的标志
bool g_authed = false;

void finish_socket_auth_task(
    const boost::system::error_code& ec,
    std::size_t bytes_transferred,
    const tcp_connection_ptr& connection,
    const boost::shared_ptr<std::string>& data
) {
    if(ec && ec != boost::asio::error::eof) {
        std::cerr << "finsh_socket_auth_task: Client error on recieve: " << ec.message() << '\n';
        assert(false);
    }

    if(bytes_transferred != 2) {
        std::cerr << "finish_socket_auth_task: wrong bytes count\n";
        assert(false);
    }

    data->resize(bytes_transferred);
    if(*data != "OK") {
        std::cerr << "finish_socket_auth_task: wrong response " << *data << '\n';
        assert(false);
    }

    g_authed = true;
    // 关闭TCP双向连接
    connection.shutdown();
    tasks_processor::get().stop();
}

// 接收认证服务器发回的消息的函数
void receive_auth_task(const boost::system::error_code& ec, const tcp_connection_ptr& connection, 
    const boost::shared_ptr<std::string>& data) {
    if(ec) {
        std::cerr << "receive_auth_task: client error on receive: " << ec.message() << '\n';
        assert(false);
    }

    tcp_connection_ptr soc(connection);
    soc.async_read(
        boost::asio::buffer(&(*data)[0], data->size()),
        [soc, data](const boost::system::error_code& ec, std::size_t bytes_transferred) {
                finish_socket_auth_task(ec, bytes_transferred, soc, data);
        },
        1
    );

}

const unsigned short port_num = 65001;
// 客户端发送auth的函数
void send_auth_task() {
    tcp_connection_ptr soc = tasks_processor::get().create_connection("127.0.0.1", port_num);
    boost::shared_ptr<std::string> data = boost::make_shared<std::string>("authname");

    soc.async_write(
        boost::asio::buffer(*data),
        [soc, data](const boost::system::error_code& ec, std::size_t bytes_transferred) {
            receive_auth_task(ec, soc, data);
        }
    );
}

int main(int argc, char* argv[]) {
    // 一秒钟之后发起请求，因为要等服务器先启动起来
    tasks_processor::get().run_after(boost::posix_time::seconds(1), &send_auth_task);
    // 在65001的TCP V4端口，启动auth服务器
    tasks_processor::get().add_listener(port_num, &authorizer::on_connection_accept);
    
    // 没有开始跑，
    assert(!g_authed);

    tasks_processor::get().start();
    assert(g_authed);
    return 0;
}