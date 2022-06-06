#include <boost/noncopyable.hpp>
#include <boost/thread/tss.hpp>
#include <boost/thread/thread.hpp>

#include <iostream>

#include <cassert>

class connection: boost::noncopyable {
public:
    int open_count_;
    connection(): open_count_(0) {}

    void open();
    void send_result(int result);
};

// 打开连接，简单的设置 open_count_ = 1
void connection::open() {
    assert(!open_count_);
    open_count_ = 1;
}

void connection::send_result(int /*result*/) {}

connection& get_connection();

// 类似Java中的 thread_local变量，一个线程一份
boost::thread_specific_ptr<connection> connection_ptr;

connection& get_connection() {
    connection* p = connection_ptr.get();
    // 还未初始化
    if(!p) {
        // 初始化连接对象
        std::cerr << "开始初始化连接, 线程ID: " << boost::this_thread::get_id() << std::endl;
        connection_ptr.reset(new connection());
        p = connection_ptr.get();
        p->open();
    }
    return *p;
}

void task() {
    int result = 2;
    get_connection().send_result(result);
}

void run_tasks() {
    for(std::size_t i=0; i<10000000; ++i) {
        task();
    }
}

int main(int argc, char* argv[]) {

    boost::thread t1;
    
    boost::thread_group threads;
    for(std::size_t i=0; i<4; ++i) {
        threads.create_thread(&run_tasks);
    }
    threads.join_all();
    return 0;
}

