#include <iostream>
using std::cout;
using std::endl;

#include <boost/array.hpp>
#include <boost/asio.hpp>

using namespace boost::asio;
using boost::asio::ip::tcp;

// 程序测试方法
// ./main time.nist.gov
// 后面这台服务器上面有可用的daytime服务

int main(int argc, char* argv[]) {
    // 命令行参数个数小于2个
    if(argc != 2) {
        std::cerr << "Usage: client [host]" << endl;
        return 1;
    }

    io_service io_service;

    tcp::resolver resolver(io_service);
    // argv[1] 是host名, daytime代表知名端口13号端口
    // resolver 会到/etc/services文件中查找服务对应的端口
    tcp::resolver::query query(argv[1], "daytime"); 
    tcp::resolver::iterator endpoint_it = resolver.resolve(query);

    tcp::socket socket(io_service);
    connect(socket, endpoint_it);

    try {
        for(;;){
        
            boost::array<char, 128> buf;
            boost::system::error_code error;
            size_t len = socket.read_some(buffer(buf), error);
            // 出现eof错误说明读完了网络流
            // 这样写表示由服务端主动关闭连接
            if(error == boost::asio::error::eof) {
                break;
            } else if(error) {
                throw boost::system::system_error(error);
            }
            cout.write(buf.data(), len);

        }
    }catch(std::exception& ex) {
        // 打印异常信息
        std::cerr << ex.what() << endl;
    }

    return 0;
}
