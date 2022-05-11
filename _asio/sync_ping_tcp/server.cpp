#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <vector>
#include <iostream>
#include <sstream>
using namespace boost::asio;
using namespace boost::posix_time;

io_service service;

struct talk_to_client;
using client_ptr = boost::shared_ptr<talk_to_client>;
using array = std::vector<client_ptr>;

array clients;  // 全局的客户端连接数组对象

boost::recursive_mutex cs;

void update_client_changed(); // 更新每个客户端client_changed字段的全局函数

struct talk_to_client: public boost::enable_shared_from_this<talk_to_client> {
    talk_to_client(): sock_(service), started_(false), already_read_(0) {
        last_ping = microsec_clock::local_time();
    }

    std::string username() const {return username_;}
    void set_client_changed() {
        clients_changed_ = true;
    }
    
    ip::tcp::socket& sock() {
        return sock_;
    }

    void stop() {
        boost::system::error_code err;
        sock_.close(err);
    }
    
    // 返回给客户端的函数
    void answer_to_client() {
        try {
            // 不断读取请求数据，处理请求数据
            read_request();
            process_request();
        }catch(boost::system::system_error&) {
            stop();
        }
            
        // 如果ping的时间过期，直接关掉连接
        if(timed_out()) {
            stop();
            std::cout << "stopping " << username_ << "- no ping intime" << std::endl;
        }
    }
    
    // 超过 5 秒就认为超时
    bool timed_out() const {
        ptime now = microsec_clock::local_time();
        long long ms = (now - last_ping).total_milliseconds();
        return ms > 5000;
    }

    private:

        void read_request() {
            // 有的读
            if(sock_.available()) {
                already_read_ += sock_.read_some(buffer(buff_ + already_read_, max_msg - already_read_));
            }
        }

        void process_request() {
            bool found_enter = std::find(buff_ , buff_ + already_read_, '\n') < buff_ + already_read_;
            if(!found_enter) {
                return;
            }

            last_ping = microsec_clock::local_time();
            // 首先把已经满了的消息读出来
            std::size_t pos = std::find(buff_,  buff_ + already_read_, '\n') - buff_;
            std::string msg(buff_, pos);
            
            // 接着把没有读完的消息重新写入buff_
            // 能这样写的原因是每次只发送到换行符就不发了
            std::copy(buff_ + already_read_, buff_ + max_msg, buff_);
            // 复位already_read_变量
            already_read_ -= pos +1;
            
            if(msg.find("login") == 0) on_login(msg);
            else if(msg.find("ping") == 0) on_ping();
            else if(msg.find("ask_clients") == 0) on_clients(); 
            else std::cerr << "invalid msg: " << msg << std::endl;
        }

        void on_login(const std::string& msg) {
            std::istringstream in(msg);
            in >> username_ >> username_;
            std::cout << username_ << "logged in" << std::endl;
            write("login ok\n");
            update_client_changed();
        }

        void on_ping() {
            write(clients_changed_? "ping client_list_changed\n": "ping ok\n");
            // 处理完成之后复位clients_changed_状态
            clients_changed_ = false;
        }
        
        // 返回所有的clients的用户名信息
        void on_clients() {
            std::string msg;
            {
                boost::recursive_mutex::scoped_lock lk(cs);
                for(array::const_iterator b = clients.begin(), e = clients.end(); b != e; ++b) {
                    msg += (*b)->username() + " ";
                }
            }
            write("clients " + msg + "\n");
        }

        void write(const std::string& msg) {
            sock_.write_some(buffer(msg));
        }

        ip::tcp::socket sock_;
        enum {max_msg = 1024};
        int already_read_;
        char buff_[max_msg];
        bool started_;
        std::string username_;
        bool clients_changed_;
        ptime last_ping;
};

void update_client_changed() {
    boost::recursive_mutex::scoped_lock lk(cs);
    for(array::iterator b = clients.begin(), e = clients.end(); b!=e; ++b) {
        (*b)->set_client_changed();
    }
}


void accept_thread() {
    ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8001));
    // 死循环，一直接收新连接
    while(true) {
        auto new_ = boost::make_shared<talk_to_client>();
        acceptor.accept(new_->sock());
        boost::recursive_mutex::scoped_lock lk(cs);
        clients.emplace_back(new_);
    }
}

void handle_clients_thread() {
    while(true) {
        boost::this_thread::sleep(millisec(1));
        boost::recursive_mutex::scoped_lock ls(cs);
        for(array::iterator b = clients.begin(), e = clients.end(); b!=e; ++b) {
            (*b)->answer_to_client();
        } 
        // 清除掉timed_out的客户端
        clients.erase(std::remove_if(clients.begin(), clients.end(), [](const auto& ptr){
                        return ptr->timed_out();
                    } ), clients.end());
    }
}

int main(int argc, char* argv[]) {
    boost::thread_group groups;
    groups.create_thread(accept_thread);
    groups.create_thread(handle_clients_thread);
    groups.join_all();
}


