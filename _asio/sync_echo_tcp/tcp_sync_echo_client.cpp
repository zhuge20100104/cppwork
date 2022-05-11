#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>
#include <string>

using namespace boost::asio;
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


ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8001);

void sync_echo(std::string msg) {
    msg += "\n";
    ip::tcp::socket sock(service);
    sock.connect(ep);
    sock.write_some(buffer(msg));
    char buff[1024];
    char* buf = buff;
    int bytes = read(sock, buffer(buff), [buf](const boost::system::error_code& ec, std::size_t bytes_){
                return read_complete(buf, ec, bytes_);
            });
    // bytes-1 是为了去掉换行符, copy中是回显字符
    std::string copy(buf, bytes - 1);
    // 原字符为msg，同样去掉换行符
    msg = msg.substr(0, msg.size()-1);
    std::cout << "server echoed our message: " << msg << ": " << (copy == msg? "OK": "FAIL") << std::endl;

    sock.close();
}

int main(int argc, char* argv[]) {
    const char* messages[] ={
        "John says hi", "so does james", "Lucy just got home", "Boost.Asio is fun", "中良hello", 0
    };

    boost::thread_group threads;
    for(const char** message = messages; *message; ++message) {
        threads.create_thread([message]() {
                    sync_echo(*message);
                });
        boost::this_thread::sleep(boost::posix_time::millisec(100));
    }

    threads.join_all();
}


